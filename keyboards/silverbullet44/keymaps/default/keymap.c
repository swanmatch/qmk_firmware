/* Copyright 2019 SwanMatch
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
     *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
//enum custom_keycodes {
//  QMKBEST = SAFE_RANGE,
//  QMKURL
//};
enum layer {
    _QWERTY,
    _CURSOR,
    _CALC,
    _ADJUST,
};

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  KC_00,
  ALTAB,
  SALTAB
};
#define CALC     LT(_CALC,   KC_ESC)
#define CRSR     LT(_CURSOR, KC_TAB)
#define ALT_F5   LALT_T(KC_F5)
#define SFT_SPC  LSFT_T(KC_SPC)
#define CTRL_ENT LCTL_T(KC_ENT)
#define GUI_F12  GUI_T(KC_F12)
#define ALT_BSPC LALT_T(KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                                  |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |Shift |   A  |   S  |   D  |   F  |   G  |                                  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  |-------.-------.  ,---------------|   N  |   M  |   ,  |   .  |   /  |  -   |
 * `-----------------------------------------/       /       /   \       \      \----------------------------------------'
 *                          | Alt  | Bksp | / Shift / Calc  /     \ Cursol\ Ctrl | Del  |  App  |
 *                          |  F5  |      |/ Space /  Esc  /       \  Tab  \ Enter\     |  F12  |
 *                          `-----------------------------'         '---------------------------'
 */
  [_QWERTY] = LAYOUT(
    KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T,                KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_EQL,
    KC_LSFT,  KC_A, KC_S, KC_D, KC_F, KC_G,                KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LCTL,  KC_Z, KC_X, KC_C, KC_V, KC_B,                KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
                  ALT_F5, ALT_BSPC, SFT_SPC, CALC,    CRSR, CTRL_ENT, KC_DEL, GUI_F12
  ),

/* Cursor
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |      |  F1  |  F2  | PgUp |  F4  |  F5  |                                  |  F6  |  F7  |  Up  |  F9  | F10  |Reset |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  ~   | Home | PgDw | End  |  (   |                                  |  )   | Left | Down |Right | F8   | F11  |
 * |------+------+------+------+------+------+                                  +------+------+------+------+------+------|
 * |      |  `   | CLft |  F3  | CRgt |SALTAB|-------.-------.  ,---------------|ALTTAB| OSL  |  F8  | OSR  |      |      |
 * `-----------------------------------------/       /       /   \       \      \----------------------------------------'
 *                          |      |      | /       /       /     \       \      \  |      |      |
 *                          |      |      |/       /       /       \       \      \ |      |      |
 *                          `-----------------------------'         '-----------------------------'
 */
  [_CURSOR] = LAYOUT(
    _______, KC_F1,   KC_F2,      KC_PGUP, KC_F4,      KC_F5,                              KC_F6,   KC_F7,        KC_UP,   KC_F9,        KC_F10,  QK_RBT,
    _______, KC_TILD, KC_HOME,    KC_PGDN, KC_END,     KC_LPRN,                            KC_RPRN, KC_LEFT,      KC_DOWN, KC_RGHT,      KC_PIPE, KC_F11,
    _______, KC_GRV,  C(KC_LEFT), KC_F3,   C(KC_RGHT), S(ALTAB),                           ALTAB,   LCA(KC_LEFT), KC_F8,   LCA(KC_RGHT), KC_BSLS, RGBRST,
                                  _______,    _______, C(KC_SPC), MO(_ADJUST),    _______, _______, _______, _______
  ),

/* Calculator
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |      |  1   |  2   |  3   |  4   |  5   |                                  |  6   |  7   |  8   |  9   |  0   |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  @   |  #   |  $   |  %   |  [   |                                  |  ]   |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  ^   |  &   |  *   |  !   |  {   |-------.-------.  ,---------------|  }   |  1   |  2   |  3   |  =   |      |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /       /       /     \       \       \  |      |      |
 *                          |      |      |/       /       /       \       \   0   \ |  00  |  .   |
 *                          `-----------------------------'         '------------------------------'
 */
  [_CALC] = LAYOUT(
    QK_RBT,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LBRC,                          KC_RBRC, KC_4,    KC_5,    KC_6,    KC_PPLS, _______,
_______, KC_CIRC, KC_AMPR, KC_ASTR, KC_EXLM, KC_LCBR,                          KC_RCBR, KC_1,    KC_2,    KC_3,    KC_PEQL, _______,
                               _______, _______, _______, _______,    MO(_ADJUST), KC_0,    KC_00,   KC_PDOT
  ),

/*   ADJUST
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |      |      |      |FrqRst|      |      |                                  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |Music |FrqUp |Sound |      |                                  | SPD+ | MOD+ | VAL+ | SAD+ | HUE+ |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |Scale |FrqDwn|      |      |-------.-------.  ,---------------| SPD- | SPD- | VAL- | SAD- | HUE- |      |
* `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /       /       /     \       \       \  |      |      |
 *                          |      |      |/       /       /       \       \       \ |      |      |
 *                          `-----------------------------'         '------------------------------'
*/

  [_ADJUST] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, CK_RST,  XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
    XXXXXXX, XXXXXXX, MU_TOGG, CK_UP,   AU_TOGG, XXXXXXX,                      RGB_SPI, RGB_MOD,  RGB_VAI, RGB_SAI, RGB_HUI, XXXXXXX,
    XXXXXXX, XXXXXXX, MU_NEXT, CK_DOWN, XXXXXXX, XXXXXXX,                      RGB_SPD, RGB_RMOD, RGB_VAD, RGB_SAD, RGB_HUD, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX, _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX
  )
};

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
int  RGB_current_mode;
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
//   iota_gfx_force_dirty();
    if (layer_state == _QWERTY) {
        switch (index) {
            case 0: /* left encoder */
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case 1: /* right encoder */
                if (clockwise) {
                    tap_code(KC_MS_WH_UP);
                } else {
                    tap_code(KC_MS_WH_DOWN);
                }
                break;
        }
} else {
      #ifdef RGBLIGHT_ENABLE
        switch (index) {
            case 0: /* left encoder */
                if (clockwise) {
                    rgblight_increase_hue_noeeprom();
                } else {
                    rgblight_decrease_hue_noeeprom();
                }
                break;
            case 1: /* right encoder */
                if (clockwise) {
                    rgblight_increase_sat_noeeprom();
                } else {
                    rgblight_decrease_sat_noeeprom();
                }
                break;
        }
      #endif
    }
    return true;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef RGBLIGHT_ENABLE
        case RGBRST:
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
            }
            break;
#endif
#ifndef VIA_ENABLE
        case KC_SCLN:
            if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
                if (record->event.pressed) {
                    unregister_code(KC_LSFT);
                    tap_code16(keycode);
                    register_code(KC_LSFT);
                }
            } else {
                if (record->event.pressed) {
                    tap_code16(S(keycode));
                }
            }
            return false;
            break;
        case KC_00:
            if (record->event.pressed) {
                tap_code(KC_0);
                register_code(KC_0);
            } else {
                unregister_code(KC_0);
            }
            return false;
            break;
#endif
    }
    return true;
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
}


#ifdef TOUCH_ENABLE

#include "mtch6102.h"
#include "pointing_device.h"
void matrix_scan_user() {

    // Change cursor movement to scroll movement if layer is _CURSOL
    if (layer_state_is(_CURSOR)) {
        report_mouse_t mouse_rep = pointing_device_get_report();
        if (mouse_rep.x != 0) {
            mouse_rep.h = mouse_rep.x > 0 ? 1 : -1;
            mouse_rep.x = 0;
        }

        if (mouse_rep.y != 0) {
            mouse_rep.v = mouse_rep.y > 0 ? 1 : -1;
            mouse_rep.y = 0;
        }

        pointing_device_set_report(mouse_rep);
    }
}

#endif
