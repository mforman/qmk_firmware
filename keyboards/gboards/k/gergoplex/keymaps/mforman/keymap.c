#include QMK_KEYBOARD_H
#include "mforman.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_gergoplex(
KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,     KC_Y   , KC_U   , KC_I    , KC_O   , KC_P    ,
KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,     KC_H   , KC_J   , KC_K    , KC_L   , KC_QUOT ,
KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,     KC_N   , KC_M   , KC_COMM , KC_DOT , KC_SLSH ,

                  TC_ESC , TC_SPC , TC_TAB ,     TC_ENT , TC_BSP , TC_DEL
),

[_WINDOWS] = LAYOUT_gergoplex(
_______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,

  LCTL_T(KC_ESC), LGUI_T(KC_SPACE), _______,     _______, _______, _______
),

[_LOWER] = LAYOUT_gergoplex(
KC_F12       , KC_F7       , KC_F8       , KC_F9       , RESET  ,     KC_INS , KC_HOME, KC_PGDN, KC_PGUP, KC_END ,
GUI_T(KC_F11), ALT_T(KC_F4), CTL_T(KC_F5), SFT_T(KC_F6), KC_VOLU,     KC_CAPS, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT,
KC_F10       , KC_F1       , KC_F2       , KC_F3       , KC_VOLD,     TG_WIN , KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,

                             _______     , _______     , _______,     KC_BTN1, KC_BTN2, KC_BTN3
),

[_RAISE] = LAYOUT_gergoplex(
_______, KC_7   , KC_8   , KC_9   , _______,    _______, KC_LEFT_PAREN , KC_PLUS      , KC_RIGHT_PAREN, _______       ,
KC_COLN, KC_4   , KC_5   , KC_6   , KC_GRV ,    KC_MINS, SFT_T(KC_LBRC), CTL_T(KC_EQL), ALT_T(KC_RBRC), GUI_T(KC_SCLN),
KC_PIPE, KC_1   , KC_2   , KC_3   , _______,    _______, KC_LCBR       , KC_TILD      , KC_RCBR       , KC_BSLASH     ,

                  KC_DOT , KC_0   , _______,    _______, _______, _______
)
};

#include "mforman.c"
