#include QMK_KEYBOARD_H
#include "mforman.h"  // in users/mforman
#include "config.h"
#include "lib/lib8tion/lib8tion.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

extern uint8_t is_master;

// clang-format off
#define LAYOUT_crkbd_wrapper(...)   LAYOUT_split_3x6_3(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_crkbd_wrapper(
    KC_TAB , _________________QWERTY_L1_________________,     _________________QWERTY_R1_________________, _______,
    _______, _________________QWERTY_L2_________________,     _________________QWERTY_R2_________________, _______,
    _______, _________________QWERTY_L3_________________,     _________________QWERTY_R3_________________, _______,

                               TC_ESC , TC_SPC , TC_TAB ,     TC_ENT , TC_BSP , TC_DEL
),

  [_COLEMAK] = LAYOUT_crkbd_wrapper(
    KC_TAB , _________________COLEMAK_L1________________,     _________________COLEMAK_R1________________, _______,
    _______, _________________COLEMAK_L2________________,     _________________COLEMAK_R2________________, _______,
    _______, _________________COLEMAK_L3________________,     _________________COLEMAK_R3________________, _______,

                               TC_ESC , TC_SPC , TC_TAB ,     TC_ENT , TC_BSP , TC_DEL
),

  [_WINDOWS] = LAYOUT_crkbd_wrapper(
    _______, ___________________BLANK___________________,      ___________________BLANK___________________, _______,
    _______, ___________________BLANK___________________,      ___________________BLANK___________________, _______,
    _______, ___________________BLANK___________________,      ___________________BLANK___________________, _______,

               LCTL_T(KC_ESC), LGUI_T(KC_SPACE), _______,      _______, _______, _______
  ),

  [_LOWER] = LAYOUT_crkbd_wrapper(
    _______, _________________LOWER_L1__________________,      _________________LOWER_R1__________________, _______,
    _______, _________________LOWER_L2__________________,      _________________LOWER_R2__________________, _______,
    _______, _________________LOWER_L3__________________,      _________________LOWER_R3__________________, _______,

                               _______, _______, _______,      _______, KC_BTN1, KC_BTN2
),

  [_RAISE] = LAYOUT_crkbd_wrapper(
    _______, _________________RAISE_L1__________________,      _________________RAISE_R1__________________, _______,
    _______, _________________RAISE_L2__________________,      _________________RAISE_R2__________________, _______,
    _______, _________________RAISE_L3__________________,      _________________RAISE_R3__________________, _______,

                               KC_DOT , KC_0   , _______,      _______, _______, _______
),

  [_ADJUST] = LAYOUT_crkbd_wrapper(
    _______, ________________ADJUST_L1__________________,      ________________ADJUST_R1__________________, _______,
    _______, ________________ADJUST_L2__________________,      ________________ADJUST_R2__________________, _______,
    _______, ________________ADJUST_L3__________________,      ________________ADJUST_R3__________________, _______,

                               _______, _______, _______,      _______, _______, _______
)
};
// clang-format on
int RGB_current_mode;

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#    ifndef SPLIT_KEYBOARD
    if (is_master) {
#    endif
        return OLED_ROTATION_270;
#    ifndef SPLIT_KEYBOARD
    }  else {
        return rotation;
    }
#    endif
}

void render_space(void) { oled_write_P(PSTR("     "), false); }

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[]  = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[]  = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[]  = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[]  = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[]  = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[]  = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[]  = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[]  = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,  0,  0,  0,192,224,240,240,240,240,240,240,240,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,240,  0,  0,240,252,254,255,255,255,  1,240,252,255,255,255,255,255,255,255,255,127, 31,  7,  0,  0,  0,  0,  0,  0,  0,  0,240,248,252, 30, 14, 14, 14, 14, 14, 14, 30, 60, 56, 48,  0,  0,240,248,252, 30, 14, 14, 14, 14, 14, 14, 30,252,248,240,  0,  0,254,254,252, 28, 14, 14, 14, 14,  0,  0,254,254,252, 28, 14, 14, 14, 14, 30,252,248,240,  0,  0,240,248,252,222,206,206,206,206,206,206,222,252,248,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,255,255,254,240,255,255,255,255,255,255,248,255,255,255,255,255,255,255,255,255,193,128,128,128,192,240,  0,  0,  0,  0,  0,  0, 15, 31, 63,120,112,112,112,112,112,112,120, 60, 28, 12,  0,  0, 15, 31, 63,120,112,112,112,112,112,112,120, 63, 31, 15,  0,  0,127,127,127,  0,  0,  0,  0,  0,  0,  0,127,127,127,  0,  0,  0,  0,  0,  0,127,127,127,  0,  0, 15, 31, 63,121,113,113,113,113,113,113,121, 61, 29, 13,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  3,  3,  1,  1,  3,  3,  7,  7,  7,  3,  3,  1,  3,  7,  7,  7,  7,  7,  7,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));

}

void render_layout_name(void) {
    oled_write_P(PSTR("Lyout"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWRTY"), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR("COLE "), false);
            break;
    }
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0
    };
    static const char PROGMEM raise_layer[]   = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0
    };
    static const char PROGMEM lower_layer[]   = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0
    };
    static const char PROGMEM adjust_layer[]  = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0
    };
    if (layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);
    } else if (layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if (layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_os_config(void) {
    static const char PROGMEM apple[] = {
        0x20, 0x80, 0x81, 0x20, 0x20,
        0x20, 0xa0, 0xa1, 0x20, 0x20, 0
    };
    static const char PROGMEM windows[]   = {
        0x20, 0x82, 0x83, 0x20, 0x20,
        0x20, 0xa2, 0xa3, 0x20, 0x20, 0
    };
    if (layer_state_is(_WINDOWS)) {
        oled_write_P(windows, false);
    } else {
        oled_write_P(apple, false);
    }
}

void render_status_main(void) {
    render_layout_name();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods() | get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods() | get_oneshot_mods());
    render_space();
    render_os_config();
}

void render_status_secondary(void) {
    render_logo();
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#    ifndef SPLIT_KEYBOARD
    else {
        oled_on();
    }
#    endif

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
        // set_timelog();
    }

    switch (keycode) {
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
#ifdef RGB_MATRIX_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgb_matrix_default();
                rgb_matrix_enable();
            }
#endif
            break;
        case KC_RGB_T:  // This allows me to use underglow as layer indication, or as normal
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                userspace_config.rgb_layer_change ^= 1;
                dprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
                eeconfig_update_user(userspace_config.raw);
                if (userspace_config.rgb_layer_change) {
#    if defined(RGBLIGHT_ENABLE) && defined(RGB_MATRIX_ENABLE)
                    rgblight_enable_noeeprom();
#    endif
                    layer_state_set(layer_state);  // This is needed to immediately set the layer color (looks better)
#    if defined(RGBLIGHT_ENABLE) && defined(RGB_MATRIX_ENABLE)
                } else {
                    rgblight_disable_noeeprom();
#    endif
                }
            }
#endif  // RGBLIGHT_ENABLE
            break;
        case RGB_IDL:  // This allows me to use underglow as layer indication, or as normal
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
                if (record->event.pressed) {
                    userspace_config.rgb_matrix_idle_anim ^= 1;
                    dprintf("RGB Matrix Idle Animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
                    eeconfig_update_user(userspace_config.raw);
                    if (userspace_config.rgb_matrix_idle_anim) {
                        rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
                    }
                }
#endif
            break;
            case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT:  // quantum_keycodes.h L400 for definitions
                if (record->event.pressed) {
                    bool is_eeprom_updated;
#    if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                    // This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
                    if (userspace_config.rgb_layer_change) {
                        userspace_config.rgb_layer_change = false;
                        dprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
                        is_eeprom_updated = true;
                    }
#    endif
#    if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
                    if (userspace_config.rgb_matrix_idle_anim) {
                        userspace_config.rgb_matrix_idle_anim = false;
                        dprintf("RGB Matrix Idle Animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
                        is_eeprom_updated = true;
                    }
#    endif
                    if (is_eeprom_updated) {
                        eeconfig_update_user(userspace_config.raw);
                    }
                }

#    if defined(RGBLIGHT_DISABLE_KEYCODES) || defined(RGB_MATRIX_DISABLE_KEYCODES)
                if (keycode == RGB_MODE_FORWARD && record->event.pressed) {
                    uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
                    if (shifted) {
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_step_reverse();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_step_reverse();
#        endif
                    } else {
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_step();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_step();
#        endif
                    }
                } else if (keycode == RGB_MODE_REVERSE && record->event.pressed) {
                    uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
                    if (shifted) {
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_step();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_step();
#        endif
                    } else {
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_step_reverse();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_step_reverse();
#        endif
                    }
                } else if (keycode == RGB_HUI) {
#        ifndef SPLIT_KEYBOARD
                    if (record->event.pressed) {
#        else
                    if (!record->event.pressed) {
#        endif
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_increase_hue();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_increase_hue();
#        endif
                    }
                } else if (keycode == RGB_HUD) {
#        ifndef SPLIT_KEYBOARD
                    if (record->event.pressed) {
#        else
                    if (!record->event.pressed) {
#        endif
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_decrease_hue();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_decrease_hue();
#        endif
                    }
                } else if (keycode == RGB_SAI) {
#        ifndef SPLIT_KEYBOARD
                    if (record->event.pressed) {
#        else
                    if (!record->event.pressed) {
#        endif
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_increase_sat();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_increase_sat();
#        endif
                    }
                } else if (keycode == RGB_SAD) {
#        ifndef SPLIT_KEYBOARD
                    if (record->event.pressed) {
#        else
                    if (!record->event.pressed) {
#        endif
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_decrease_sat();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_decrease_sat();
#        endif
                    }
                } else if (keycode == RGB_VAI) {
#        ifndef SPLIT_KEYBOARD
                    if (record->event.pressed) {
#        else
                    if (!record->event.pressed) {
#        endif
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_increase_val();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_increase_val();
#        endif
                    }
                } else if (keycode == RGB_VAD) {
#        ifndef SPLIT_KEYBOARD
                    if (record->event.pressed) {
#        else
                    if (!record->event.pressed) {
#        endif
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_decrease_val();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_decrease_val();
#        endif
                    }
                } else if (keycode == RGB_SPI) {
                    if (record->event.pressed) {
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_increase_speed();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_increase_speed();
#        endif
                    }
                } else if (keycode == RGB_SPD) {
                    if (record->event.pressed) {
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                        rgblight_decrease_speed();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                        rgb_matrix_decrease_speed();
#        endif
                    }
                }
                return false;
#    endif
        default:
            return true;
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) { rgb_matrix_set_suspend_state(true); }

void suspend_wakeup_init_keymap(void) { rgb_matrix_set_suspend_state(false); }

void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    switch (mode) {
        case 1:  // breathing
        {
            uint16_t time = scale16by8(g_rgb_timer, speed / 8);
            hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb       = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
        default:  // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
    }
}

void check_default_layer(uint8_t mode, uint8_t type) {
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            rgb_matrix_layer_helper(HSV_CYAN, mode, rgb_matrix_config.speed, type);
            break;
        case _COLEMAK:
            rgb_matrix_layer_helper(HSV_MAGENTA, mode, rgb_matrix_config.speed, type);
            break;
    }
}

void rgb_matrix_indicators_user(void) {
    if (userspace_config.rgb_layer_change &&
#    ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
        !g_suspend_state &&
#    endif
#    if defined(RGBLIGHT_ENABLE)
        (!rgblight_config.enable && rgb_matrix_config.enable)
#    else
        rgb_matrix_config.enable
#    endif
    ) {
        switch (get_highest_layer(layer_state)) {
            case _RAISE:
                rgb_matrix_layer_helper(HSV_BLUE, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _LOWER:
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _ADJUST:
                rgb_matrix_layer_helper(HSV_GREEN, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            default: {
                check_default_layer(0, LED_FLAG_UNDERGLOW);
                break;
            }
        }
        check_default_layer(0, LED_FLAG_MODIFIER);
    }
}

#endif

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
