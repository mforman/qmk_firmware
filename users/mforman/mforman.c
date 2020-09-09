#include "mforman.h"

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          int mod = IS_LAYER_ON(_WINDOWS) ? KC_LALT : KC_LGUI;
          register_code(mod);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case BSP_WRD:
      if (record->event.pressed) {
        int mod = IS_LAYER_ON(_WINDOWS) ? KC_LCTL : KC_LALT;
        register_code16(mod);
        tap_code(KC_BSPACE);
        unregister_code16(mod);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > ALT_TAB_TERM) {
      int mod = IS_LAYER_ON(_WINDOWS) ? KC_LALT : KC_LGUI;
      unregister_code(mod);
      is_alt_tab_active = false;
    }
  }
}
