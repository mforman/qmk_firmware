#pragma once

enum keyboard_layers {
    _QWERTY = 0,
    _COLEMAK,
    _WINDOWS,
    _LOWER,
    _RAISE
};

enum mforman_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  ALT_TAB,
  BSP_WRD
};

// Thumb cluster keys
#define TC_ESC LGUI_T(KC_ESCAPE)
#define TC_SPC LCTL_T(KC_SPACE)
#define TC_TAB LT(_LOWER ,KC_TAB)
#define TC_DEL LALT_T(KC_DELETE)
#define TC_BSP LSFT_T(KC_BSPACE)
#define TC_ENT LT(_RAISE ,KC_ENTER)

#define TG_WIN TG(_WINDOWS)

#include "g/keymap_combo.h"
