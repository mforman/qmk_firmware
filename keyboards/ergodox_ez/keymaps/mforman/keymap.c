#include QMK_KEYBOARD_H
#include "config.h"
#include "version.h"

enum keyboard_layers {
    _BASE = 0,
    _WINDOWS,
    _LOWER,
    _RAISE
};

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    /*
     * ,--------------------------------------------------.    ,--------------------------------------------------.
     * |    0   |   1  |   2  |   3  |   4  |   5  |  6   |    |  38  |  39  |  40  |  41  |  42  |  43  |   44   |
     * |--------+------+------+------+------+------+------|    |------+------+------+------+------+------+--------|
     * |    7   |   8  |   9  |  10  |  11  |  12  |  13  |    |  45  |  46  |  47  |  48  |  49  |  50  |   51   |
     * |--------+------+------+------+------+------|      |    |      |------+------+------+------+------+--------|
     * |   14   |  15  |  16  |  17  |  18  |  19  |------|    |------|  52  |  53  |  54  |  55  |  56  |   57   |
     * |--------+------+------+------+------+------|  26  |    |  58  |------+------+------+------+------+--------|
     * |   20   |  21  |  22  |  23  |  24  |  25  |      |    |      |  59  |  60  |  61  |  62  |  63  |   64   |
     * `--------+------+------+------+------+-------------'    `-------------+------+------+------+------+--------'
     *   |  27  |  28  |  29  |  30  |  31  |                                |  65  |  66  |  67  |  68  |  69  |
     *   `----------------------------------'                                `----------------------------------'
     *                                       ,-------------.  ,-------------.
     *                                       |  32  |  33  |  |  70  |  71  |
     *                                ,------+------+------|  |------+------+------.
     *                                |      |      |  34  |  |  72  |      |      |
     *                                |  35  |  36  |------|  |------|  74  |  75  |
     *                                |      |      |  37  |  |  73  |      |      |
     *                                `--------------------'  `--------------------'
     */

[_BASE] = LAYOUT_ergodox_pretty(
_______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
_______, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , _______,      _______, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , _______,
_______, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                        KC_H   , KC_J   , KC_K   , KC_L   , KC_QUOT, _______,
_______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______,      _______, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______,
_______, _______, _______, _______, TC_ESC ,                                          TC_DEL , _______, _______, _______, _______,

                                            _______, _______,       _______, _______,
                                                     _______,       _______,
                                    TC_SPC , TC_TAB, _______,       _______, TC_ENT , TC_BSP
),

[_WINDOWS] = LAYOUT_ergodox_pretty(
_______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, LCTL_T(KC_ESC),                                   _______, _______, _______, _______, _______,

                                             _______, _______,       _______, _______,
                                                      _______,       _______,
                           LGUI_T(KC_SPACE), _______, _______,       _______, _______, _______
),

[_LOWER] = LAYOUT_ergodox_pretty(
_______, _______      , _______     , _______     , _______     , _______, _______,      _______, _______, _______, _______, _______, _______, _______,
_______, KC_F12       , KC_F7       , KC_F8       , KC_F9       , RESET  , _______,      _______, KC_INS , KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______,
_______, GUI_T(KC_F11), ALT_T(KC_F4), CTL_T(KC_F5), SFT_T(KC_F6), KC_VOLU,                        KC_CAPS, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______,
_______, KC_F10       , KC_F1       , KC_F2       , KC_F3       , KC_VOLD, _______,      _______, TG_WIN , KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,
_______, _______      , _______     , _______     , _______     ,                                          KC_BTN3, _______, _______, _______, _______,

                                                                  _______, _______,      _______, _______,
                                                                           _______,      _______,
                                                         _______, _______, _______,      _______, KC_BTN1, KC_BTN2
),

[_RAISE] = LAYOUT_ergodox_pretty(
_______, _______, _______, _______, _______, _______, _______,      _______, _______, _______       , _______      , _______       , _______       , _______,
_______, _______, KC_7   , KC_8   , KC_9   , _______, _______,      _______, _______, KC_LEFT_PAREN , KC_PLUS      , KC_RIGHT_PAREN, _______       , _______,
_______, KC_COLN, KC_4   , KC_5   , KC_6   , KC_GRV ,                        KC_MINS, SFT_T(KC_LBRC), CTL_T(KC_EQL), ALT_T(KC_RBRC), GUI_T(KC_SCLN), _______,
_______, KC_PIPE, KC_1   , KC_2   , KC_3   , _______, _______,      _______, _______, KC_LCBR       , KC_TILD      , KC_RCBR       , KC_BSLASH     , _______,
_______, _______, _______, _______, KC_DOT ,                                          _______       , _______      , _______       , _______       , _______,

                                             _______, _______,      _______, _______,
                                                      _______,      _______,
                                    KC_0   , _______, _______,      _______, _______, _______
)
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case _WINDOWS:
      ergodox_right_led_2_on();
      break;
    case _LOWER:
      ergodox_right_led_3_on();
      break;
    case _RAISE:
      ergodox_right_led_1_on();
      break;
    default:
      break;
  }
  return state;
};
