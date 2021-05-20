#include QMK_KEYBOARD_H

enum unicode_names {
    UML_A,
    UML_U_A,
};

const uint32_t PROGMEM unicode_map[] = {
    [UML_A]  = 0x00E4,
    [UML_U_A]  = 0x00C4,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi(
        KC_GESC,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,               KC_MINS,  KC_EQL, KC_BSPC,  KC_DEL,
        KC_TAB,            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,               KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_LCTL,           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,               KC_QUOT,           KC_ENT, KC_PGUP,
        KC_LSFT,                    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT,               KC_SLSH, KC_RSFT,   KC_UP, KC_PGDN,
        OSL(1),            KC_LGUI, KC_LALT,                            KC_SPC,                  OSL(1),  OSL(3), MT(MOD_RCTL, KC_CAPS), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_65_ansi(
        _______,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______,        _______, _______, _______, _______, _______, _______, KC_PGUP,   KC_UP, KC_PGDN, KC_PSCR, KC_SLCK, KC_PAUS, _______,  KC_END,
        _______,        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,  KC_INS,  KC_DEL,          _______, KC_PGDN,
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_MUTE,
        _______,        _______, _______,                             KC_SPC,                   _______,   MO(2), _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),
    [2] = LAYOUT_65_ansi(
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______, _______, RESET, _______,
        _______,        RGB_SPI, RGB_SPD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______, _______,          EEP_RST, _______,
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______,                            KC_SPC,                    _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT_65_ansi(
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, UC_M_LN,          _______, _______, _______, _______,
        _______,      XP(UML_A, UML_U_A), _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______, _______,
        _______,                          _______, _______, _______, _______, _______, _______, _______, UC_M_WC, _______,          _______, UC_MOD,  _______, _______,
        _______,                 _______, _______,                             KC_SPC,                   _______, _______, _______, _______, UC_RMOD, _______
    )
};
