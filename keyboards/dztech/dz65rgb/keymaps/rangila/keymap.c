#include QMK_KEYBOARD_H

#define _0 0
#define _1 1
#define _2 2
#define _3 3

enum unicode_names {
    UML_A,
    UML_U_A,
};

const uint32_t PROGMEM unicode_map[] = {
    [UML_A]  = 0x00E4,
    [UML_U_A]  = 0x00C4,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    CTRL_FN_LAYER,
};

td_state_t cur_dance(qk_tap_dance_state_t *state);
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_0] = LAYOUT_65_ansi(
        KC_GESC,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,               KC_MINS,  KC_EQL, KC_BSPC,  KC_DEL,
        KC_TAB,            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,               KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        TD(CTRL_FN_LAYER), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,               KC_QUOT,           KC_ENT, KC_PGUP, 
        KC_LSFT,                    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT,               KC_SLSH, KC_RSFT,   KC_UP, KC_PGDN,
        OSL(_1),            KC_LGUI, KC_LALT,                         KC_SPC,                   OSL(_1),  OSL(_3), MT(MOD_RCTL, KC_CAPS), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_1] = LAYOUT_65_ansi(
        _______,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______,        _______, _______, _______, _______, _______, _______, KC_PGUP,   KC_UP, KC_PGDN, KC_PSCR, KC_SLCK, KC_PAUS, _______,  KC_END,
        _______,        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,  KC_INS,  KC_DEL,          _______, KC_PGDN,
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_MUTE,
        _______,        _______, _______,                             KC_SPC,                   _______,   MO(_2), _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),
    [_2] = LAYOUT_65_ansi(
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______, _______, RESET, _______,
        _______,        RGB_SPI, RGB_SPD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______, _______,          EEP_RST, _______,
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______,                            KC_SPC,                    _______, _______, _______, _______, _______, _______
    ),
    [_3] = LAYOUT_65_ansi(
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, UC_M_LN,          _______, _______, _______, _______,
        _______,      XP(UML_A, UML_U_A), _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______, _______,
        _______,                          _______, _______, _______, _______, _______, _______, _______, UC_M_WC, _______,          _______, UC_MOD,  _______, _______,
        _______,                 _______, _______,                             KC_SPC,                   _______, _______, _______, _______, UC_RMOD, _______
    )
};


// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2)
    {
        if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    else return TD_UNKNOWN;
}

static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_LCTL);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LCTL);
            break;
        case TD_DOUBLE_TAP:
            if (layer_state_is(_1)) {
                layer_off(_1);
            } else {
                layer_on(_1);
            }
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_1);
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    switch (ql_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_LCTL);
            break;
        case TD_DOUBLE_HOLD:
            layer_off(_1);
            break;
        default:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [CTRL_FN_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};

