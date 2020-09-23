#pragma once

#include QMK_KEYBOARD_H

#include "version.h"

enum keyboard_layers {
    _QWERTY = 0,
    _WINDOWS,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum mforman_keycodes {
  ALT_TAB = SAFE_RANGE,
  BSP_WRD,
  RGBRST
};

// Thumb cluster keys
#define TC_ESC LGUI_T(KC_ESCAPE)
#define TC_SPC LCTL_T(KC_SPACE)
#define TC_TAB LT(_LOWER, KC_TAB)
#define TC_DEL LALT_T(KC_DELETE)
#define TC_BSP LSFT_T(KC_BSPACE)
#define TC_ENT LT(_RAISE, KC_ENTER)

#define TG_WIN TG(_WINDOWS)

#define MT_F11 GUI_T(KC_F11)
#define MT_F4  ALT_T(KC_F4)
#define MT_F5  CTL_T(KC_F5)
#define MT_F6  SFT_T(KC_F6)

#define MT_LBRC SFT_T(KC_LBRC)
#define MT_EQL  CTL_T(KC_EQL)
#define MT_RBRC ALT_T(KC_RBRC)
#define MT_GRV  GUI_T(KC_GRV)

#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH



#define _________________LOWER_L1__________________        KC_F12 , KC_F7  , KC_F8  , KC_F9  , KC_VOLU
#define _________________LOWER_L2__________________        MT_F11 , MT_F4  , MT_F5  , MT_F6  , KC_VOLD
#define _________________LOWER_L3__________________        KC_F10 , KC_F1  , KC_F2  , KC_F3  , XXXXXXX

#define _________________LOWER_R1__________________        KC_INS , KC_HOME, KC_PGDN, KC_PGUP, KC_END
#define _________________LOWER_R2__________________        KC_CAPS, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
#define _________________LOWER_R3__________________        XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R



#define _________________RAISE_L1__________________        KC_SLSH, KC_7   , KC_8   , KC_9   , KC_PLUS
#define _________________RAISE_L2__________________        KC_ASTR, KC_4   , KC_5   , KC_6   , KC_MINS
#define _________________RAISE_L3__________________        KC_PIPE, KC_1   , KC_2   , KC_3   , KC_COMM

#define _________________RAISE_R1__________________        XXXXXXX, KC_LPRN, KC_UNDS, KC_RPRN, XXXXXXX
#define _________________RAISE_R2__________________        KC_SCLN, MT_LBRC, MT_EQL , MT_RBRC, MT_GRV
#define _________________RAISE_R3__________________        KC_COLN, KC_LCBR, KC_TILD, KC_RCBR, KC_BSLS


#define ________________NUMBER_LEFT________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define ___________________BLANK___________________       _______, _______, _______, _______, _______


uint32_t layer_state_set_keymap(uint32_t state);
bool     process_record_keymap(uint16_t keycode, keyrecord_t *record);
void     matrix_scan_keymap(void);

