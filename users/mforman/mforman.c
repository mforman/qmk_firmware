#include "mforman.h"
#include "g/keymap_combo.h"

bool     is_alt_tab_active = false;
uint16_t alt_tab_timer     = 0;

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    int mod           = IS_LAYER_ON(_WINDOWS) ? KC_LALT : KC_LGUI;
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
        default:
            return true;
    }
    return true;
}

__attribute__((weak)) void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) { suspend_power_down_keymap(); }

__attribute__((weak)) void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) { suspend_wakeup_init_keymap(); }

__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > ALT_TAB_TERM) {
            int mod = IS_LAYER_ON(_WINDOWS) ? KC_LALT : KC_LGUI;
            unregister_code(mod);
            is_alt_tab_active = false;
        }
    }
    matrix_scan_keymap();
}

__attribute__((weak)) uint32_t layer_state_set_keymap(uint32_t state) { return state; }

uint32_t layer_state_set_user(uint32_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return layer_state_set_keymap(state);
};
