/* Copyright 2021 swanmatch
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
#include "mtch6102.h"
#include "pointing_device.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
// enum custom_keycodes {
//     QMKBEST = SAFE_RANGE,
//     QMKURL
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = {
        { KC_TAB, KC_BTN3, KC_MUTE },
        { LT(_ADJUST, KC_MPRV), KC_MPLY, KC_MNXT, KC_BTN2 }
    },
    [_ADJUST] = {
        { _______, _______, AU_TOGG },
        { _______, RGB_MOD, RGB_RMOD, RGB_TOG }
    }
};

bool encoder_update_user(uint8_t index, bool clockwise) {
//   iota_gfx_force_dirty();
    if (layer_state == _BASE) {
        switch (index) {
            case 0: /* left encoder */
                if (clockwise) {
                    tap_code(KC_TAB);
                } else {
                    tap_code16(LSFT(KC_TAB));
                }
                break;
            case 1: /* center encoder */
                if (clockwise) {
                    tap_code(KC_MS_WH_UP);
                } else {
                    tap_code(KC_MS_WH_DOWN);
                }
                break;
            case 2: /* right encoder */
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
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
            case 1: /* center encoder */
                if (clockwise) {
                    rgblight_increase_sat_noeeprom();
                } else {
                    rgblight_decrease_sat_noeeprom();
                }
                break;
            case 2: /* right encoder */
                if (clockwise) {
                    rgblight_increase_val_noeeprom();
                } else {
                    rgblight_decrease_val_noeeprom();
                }
                break;
        }
      #endif
    }
    return true;
}


void matrix_scan_user() {

    // Change cursor movement to scroll movement if layer is 1
    if (layer_state_is(1)) {
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
/*

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
