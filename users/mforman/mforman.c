#include "mforman.h"
#include "g/keymap_combo.h"

bool     is_alt_tab_active = false;
uint16_t alt_tab_timer     = 0;

userspace_config_t userspace_config;

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
        case COLEMAK:
            set_single_persistent_default_layer(_COLEMAK);
            break;
        case QWERTY:
            set_single_persistent_default_layer(_QWERTY);
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

__attribute__((weak)) void led_set_keymap(uint8_t usb_led) {}

// Any custom LED code goes here.
// So far, I only have keyboard specific code,
// So nothing goes here.
void led_set_user(uint8_t usb_led) { led_set_keymap(usb_led); }


__attribute__((weak)) void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
    userspace_config.raw = eeconfig_read_user();
    keyboard_pre_init_keymap();
}
__attribute__((weak)) void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
    userspace_config.raw              = 0;
    userspace_config.rgb_layer_change = true;
    eeconfig_update_user(userspace_config.raw);
    eeconfig_init_keymap();
    keyboard_init();
}

__attribute__((weak)) uint32_t layer_state_set_keymap(uint32_t state) { return state; }

uint32_t layer_state_set_user(uint32_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return layer_state_set_keymap(state);
};
