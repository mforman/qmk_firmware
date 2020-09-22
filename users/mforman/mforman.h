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

uint32_t layer_state_set_keymap(uint32_t state);
bool     process_record_keymap(uint16_t keycode, keyrecord_t *record);
void     matrix_scan_keymap(void);

#include "g/keymap_combo.h"
