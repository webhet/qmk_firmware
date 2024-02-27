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

#pragma once

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)

// wiring

// first half:  MCU pins
// second half: MCP pins (only placeholders)
// A0 is just a placeholder (itself not connected in hardware)
// clang-format off
#define DIRECT_PINS \
    { \
        {B0, B1, B14, A10, A13, B4}, \
        {A6, A7, B13,  A9, A14, B5}, \
        {A4, A5, B12,  A8, A15, B6}, \
        {A3, A2,  B2, B15,  B3, B7}, \
        {A0, A0,  A0,  A0,  B8, B9}, \
        {A0, A0,  A0,  A0,  A0, A0}, \
        {A0, A0,  A0,  A0,  A0, A0}, \
        {A0, A0,  A0,  A0,  A0, A0}, \
        {A0, A0,  A0,  A0,  A0, A0}, \
        {A0, A0,  A0,  A0,  A0, A0} \
    }
// clang-format on

/* i2c settings */

#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN B10
#define I2C1_SDA_PIN B11
#define I2C1_TIMINGR_PRESC 2U
#define I2C1_TIMINGR_SCLDEL 1U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 9U
#define I2C1_TIMINGR_SCLL 26U
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1
