/*
Copyright 2024 Marc Hetche <marc.hetche@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "matrix.h"
#include "debug.h"
#include "wait.h"
#include "i2c_master.h"

#define MCP23017_I2C_TIMEOUT 1000
#define I2C_WRITE 0x00
#define I2C_READ 0x01

// I2C address:
// See the datasheet, section 3.3.1 on addressing I2C devices and figure 3-6 for an
// illustration
// http://ww1.microchip.com/downloads/en/devicedoc/20001952c.pdf
// All address pins of the first mcp23017 are connected to the ground
// For the second one A2 is connected to 3.3V and A1 + A0 are connected to ground
// | 0  | 1  | 0  | 0  | A2 | A1 | A0 |
// | 0  | 1  | 0  | 0  | 0  | 0  | 0  |
#define I2C_ADDR_1 0b0100000
#define I2C_ADDR_2 0b0100100
#define I2C_ADDR_1_WRITE ((I2C_ADDR_1 << 1) | I2C_WRITE)
#define I2C_ADDR_1_READ ((I2C_ADDR_1 << 1) | I2C_READ)
#define I2C_ADDR_2_WRITE ((I2C_ADDR_2 << 1) | I2C_WRITE)
#define I2C_ADDR_2_READ ((I2C_ADDR_2 << 1) | I2C_READ)

// Register addresses
// See https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/blob/master/Adafruit_MCP23017.h
#define IODIRA 0x00 // i/o direction register
#define IODIRB 0x01
#define GPPUA 0x0C // GPIO pull-up resistor register
#define GPPUB 0x0D
#define MCP23017_GPIOA 0x12 // general purpose i/o port register (write modifies OLAT)
#define MCP23017_GPIOB 0x13
#define OLATA 0x14 // output latch register
#define OLATB 0x15

static bool         i2c_initialized                       = 0;
static i2c_status_t mcp23017_status                       = 0;
static pin_t        matrix_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;
static uint8_t      mcp23017_reset_loop;
static uint8_t      tr1_state = 0;
static uint8_t      tr2_state = 0;

static i2c_status_t read_mcp_row(matrix_row_t *current_row_value, uint8_t row_idx);

i2c_status_t init_mcp23017(void) {
    print("init mcp23017\n");
    i2c_status_t mcp23017_status_1 = I2C_ADDR_1;
    i2c_status_t mcp23017_status_2 = I2C_ADDR_2;

    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init(); // on pins D(1,0)
        i2c_initialized = true;
        wait_ms(MCP23017_I2C_TIMEOUT);
    }

    // Set pin direction.
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    uint8_t buf[] = {IODIRA, 0b11111111, 0b11111111};
    print("before pin dir transmit\n");
    mcp23017_status_1 = i2c_transmit(I2C_ADDR_1_WRITE, buf, sizeof(buf), MCP23017_I2C_TIMEOUT);
    mcp23017_status_2 = i2c_transmit(I2C_ADDR_2_WRITE, buf, sizeof(buf), MCP23017_I2C_TIMEOUT);
    uprintf("after pin dir transmit %i\n", mcp23017_status);

    // Set pull-up state.
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    uint8_t pullup_buf[] = {GPPUA, 0b11111111, 0b11111111};
    if (!mcp23017_status_1) {
        mcp23017_status_1 = i2c_transmit(I2C_ADDR_1_WRITE, pullup_buf, sizeof(pullup_buf), MCP23017_I2C_TIMEOUT);
        uprintf("after pull-up transmit %i\n", mcp23017_status_1);
    }
    if (!mcp23017_status_2) {
        mcp23017_status_2 = i2c_transmit(I2C_ADDR_2_WRITE, pullup_buf, sizeof(pullup_buf), MCP23017_I2C_TIMEOUT);
        uprintf("after pull-up transmit %i\n", mcp23017_status_2);
    }

    return mcp23017_status_1 || mcp23017_status_2;
}

void matrix_init_pins(void) {
    // Init MCU pins.
    for (uint8_t row_idx = 0; row_idx < MATRIX_ROWS_PER_SIDE; row_idx++) {
        for (uint8_t col_idx = 0; col_idx < MATRIX_COLS; col_idx++) {
            setPinInputHigh(matrix_pins[row_idx][col_idx]);
        }
    }

    // Init MCP pins.
    mcp23017_status = init_mcp23017();
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Try resetting the MCPs if there was an error.
    if (mcp23017_status != 0 && current_row == 0) {
        if (++mcp23017_reset_loop == 0) {
            // Since mcp23017_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans.
            // This will be approx bit more frequent than once per second.
            print("trying to reset mcp23017\n");
            mcp23017_status = init_mcp23017();
            if (mcp23017_status) {
                print("right side not responding\n");
            } else {
                print("right side attached\n");
            }
        }
    }

    // Start with a clear matrix row.
    matrix_row_t current_row_value = 0;

    if (current_row < MATRIX_ROWS_PER_SIDE) {
        for (uint8_t col_idx = 0; col_idx < MATRIX_COLS; col_idx++) {
            uint8_t pin_state = readPin(matrix_pins[current_row][col_idx]);

            current_row_value |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_idx);
        }
    } else {
        mcp23017_status = read_mcp_row(&current_row_value, current_row);
    }

    // Update the matrix row.
    current_matrix[current_row] = current_row_value;
}

static i2c_status_t read_mcp_row(matrix_row_t *current_row_value, uint8_t row_idx) {
    // If there was an error before do nothing.
    if (mcp23017_status) {
        return mcp23017_status;
    }

    i2c_status_t mcp_status     = mcp23017_status;
    uint8_t      reg_to_read    = MCP23017_GPIOA;
    uint8_t      i2c_read_addr  = I2C_ADDR_1_READ;
    uint8_t      i2c_write_addr = I2C_ADDR_1_WRITE;

    switch (row_idx) {
        case 5:
            reg_to_read = MCP23017_GPIOB;
            break;
        case 6:
            break;
        case 7:
            reg_to_read    = MCP23017_GPIOB;
            i2c_read_addr  = I2C_ADDR_2_READ;
            i2c_write_addr = I2C_ADDR_2_WRITE;
            break;
        case 8:
            i2c_read_addr  = I2C_ADDR_2_READ;
            i2c_write_addr = I2C_ADDR_2_WRITE;
            break;
        case 9:
            // This is read before. Handled down below.
            break;
        default:
            // Unreachable
    }

    if (row_idx == 9) {
        *current_row_value |= tr1_state;
        *current_row_value |= tr2_state << 1;
    } else {
        uint8_t buf[] = {reg_to_read};
        mcp_status    = i2c_transmit(i2c_write_addr, buf, sizeof(buf), MCP23017_I2C_TIMEOUT);
        // We read all the pins on GPIOA/GPIOB.
        // Since the connected pins are sequential, and counting from zero up, the only
        // transformations needed are a bitwise not to swap all bits and
        // a masking for the TR1 & TR2 keys.
        uint8_t data[] = {0};
        if (!mcp_status) {
            mcp_status           = i2c_receive(i2c_read_addr, data, sizeof(data), MCP23017_I2C_TIMEOUT);
            uint8_t flipped_data = ~(data[0]);
            *current_row_value   = flipped_data & 0b00111111;

            // Store TR1 & TR2 keys for later.
            switch (row_idx) {
                case 7:
                    tr1_state = (flipped_data & 0b01000000) >> 6;
                    break;
                case 8:
                    tr2_state = (flipped_data & 0b01000000) >> 6;
                    break;
                default:
            }
        }
    }

    return mcp_status;
}
