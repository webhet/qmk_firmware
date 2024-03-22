#include QMK_KEYBOARD_H

enum unicode_names { AE_LOWER, AE_UPPER, OE_LOWER, OE_UPPER, UE_LOWER, UE_UPPER, SZ, EURO };

const uint32_t PROGMEM unicode_map[] = {
    [AE_LOWER] = 0x00E4, // ä
    [AE_UPPER] = 0x00C4, // Ä
    [OE_LOWER] = 0x00F6, // ö
    [OE_UPPER] = 0x00D6, // Ö
    [UE_LOWER] = 0x00FC, // ü
    [UE_UPPER] = 0x00DC, // Ü
    [SZ]       = 0x00DF, // ß
    [EURO]     = 0x20AC, // €
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_4x6_2(
        KC_ESC,        KC_1,                   KC_2,            KC_3,                   KC_4,            KC_5,
        KC_6,          KC_7,                   KC_8,            KC_9,                   KC_0,            KC_EQUAL,

        LT(5, KC_NO),  KC_Q,                   KC_W,            KC_E,                   KC_R,            KC_T,
        KC_Y,          KC_U,                   KC_I,            KC_O,                   KC_P,            LT(6, KC_NO),

        KC_MINUS,      LSFT_T(KC_A),           LCTL_T(KC_S),    LT(2, KC_D),            LT(3, KC_F),     KC_G,
        KC_H,          LT(4, KC_J),            LT(1, KC_K),     LCTL_T(KC_L),           LSFT_T(KC_SCLN), KC_QUOTE,

        KC_LGUI,       KC_Z,                   KC_X,            LALT_T(KC_C),           KC_V,            KC_B,
        KC_N,          KC_M,                   LALT_T(KC_COMM), KC_DOT,                 KC_SLASH,        KC_BACKSLASH,

        KC_DEL,        KC_BSPC,
        LT(7, KC_SPC), KC_ENT
    ),
    [1] = LAYOUT_split_4x6_2(
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,

        KC_TRNS,        KC_TRNS,               KC_BTN1,         KC_WH_U,                KC_BTN2,         KC_TRNS,
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,

        KC_TRNS,        KC_MS_L,               KC_MS_U,         KC_MS_D,                KC_MS_R,         KC_TRNS,
        KC_TRNS,        KC_BTN1,               KC_NO,           KC_BTN2,                KC_TRNS,         KC_TRNS,

        KC_TRNS,        KC_TRNS,               KC_WH_L,         KC_WH_D,                KC_WH_R,         KC_TRNS,
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,

        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS
    ),
    [2] = LAYOUT_split_4x6_2(
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,

        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,
        KC_TRNS,        KC_TRNS,               KC_PGUP,         KC_TRNS,                KC_TRNS,         KC_TRNS,

        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_NO,                  KC_TRNS,         KC_TRNS,
        KC_TRNS,        KC_LEFT,               KC_DOWN,         KC_UP,                  KC_RGHT,         KC_TRNS,

        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,
        KC_TRNS,        KC_HOME,               KC_PGDN,         KC_END,                 KC_TRNS,         KC_TRNS,

        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS
    ),
    [3] = LAYOUT_split_4x6_2(
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,

        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,
        KC_TRNS,        KC_TILD,               KC_PIPE,         KC_QUOT,                KC_TRNS,         KC_TRNS,

        KC_TRNS,        KC_CIRC,               KC_ASTR,         KC_AMPR,                KC_NO,           KC_TRNS,
        KC_HASH,        KC_UNDS,               KC_SLSH,         KC_DQUO,                KC_DLR,          KC_TRNS,

        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,
        KC_TRNS,        KC_MINS,               KC_BSLS,         KC_GRV,                 KC_TRNS,         KC_TRNS,

        RGB_RMOD,       KC_TRNS,
        KC_TRNS,        RGB_MOD
    ),
    [4] = LAYOUT_split_4x6_2(
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,

        KC_TRNS,        KC_TRNS,               KC_COLN,         KC_LT,                  KC_GT,           KC_SCLN,
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,

        KC_TRNS,        KC_LCBR,               KC_RCBR,         KC_LPRN,                KC_RPRN,         KC_AT,
        KC_TRNS,        KC_NO,                 KC_EQL,          KC_PLUS,                KC_PERC,         KC_TRNS,

        KC_TRNS,        KC_TRNS,               KC_EXLM,         KC_LBRC,                KC_RBRC,         KC_TRNS,
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,         KC_TRNS,

        KC_VOLD,        KC_TRNS,
        KC_TRNS,        KC_VOLU
    ),
    [5] = LAYOUT_split_4x6_2(
        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,
        KC_TRNS,        KC_F10,                KC_F11,          KC_F12,                 KC_TRNS,          KC_TRNS,

        KC_NO,          KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,
        KC_TRNS,        KC_F7,                 KC_F8,           KC_F9,                  KC_TRNS,          KC_TRNS,

        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,
        KC_TRNS,        KC_F4,                 KC_F5,           KC_F6,                  KC_TRNS,          KC_TRNS,

        KC_TRNS,        KC_TRNS,               KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,
        KC_TRNS,        KC_F1,                 KC_F2,           KC_F3,                  KC_TRNS,          KC_TRNS,

        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS
    ),
    [6] = LAYOUT_split_4x6_2(
        KC_TRNS,       KC_TRNS,                KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,
        KC_TRNS,       KC_TRNS,                KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,

        KC_TRNS,       KC_TRNS,                KC_TRNS,         UM(EURO),               KC_TRNS,          KC_TRNS,
        KC_TRNS,       UP(UE_LOWER, UE_UPPER), KC_TRNS,         UP(OE_LOWER, OE_UPPER), KC_TRNS,          KC_NO,

        KC_TRNS,       UP(AE_LOWER, AE_UPPER), UM(SZ),          KC_TRNS,                KC_TRNS,          KC_TRNS,
        KC_TRNS,       KC_TRNS,                KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,

        KC_TRNS,       KC_TRNS,                KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,
        KC_TRNS,       KC_TRNS,                KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,

        KC_TRNS,       KC_LSFT,
        KC_TRNS,       KC_TRNS
    ),
    [7] = LAYOUT_split_4x6_2(
        KC_TRNS,       KC_TRNS,                KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,
        KC_TRNS,       KC_TRNS,                KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,

        KC_TRNS,       KC_TRNS,                KC_TRNS,         KC_COLN,                KC_ESC,           KC_TRNS,
        KC_TRNS,       KC_TRNS,                KC_TRNS,         KC_TRNS,                KC_DEL,           UC_NEXT,

        KC_TRNS,       KC_TRNS,                KC_TRNS,         KC_TRNS,                KC_ENT,           KC_TRNS,
        DF(1),         KC_LGUI,                KC_TRNS,         KC_TRNS,                KC_TRNS,          KC_TRNS,

        KC_TRNS,       KC_TRNS,                KC_TRNS,         KC_TRNS,                KC_EXLM,          KC_TRNS,
        DF(0),         KC_TRNS,                LALT_T(KC_COMM), LCTL_T(KC_DOT),         QK_BOOT,          KC_TRNS,

        KC_TRNS,       KC_TAB,
        KC_NO,         KC_TRNS
    )
};
// clang-format on
