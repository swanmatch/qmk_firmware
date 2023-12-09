/* Copyright 2021 swan_match
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RAISE,
    _LOWER,
    _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    KC_NAME = SAFE_RANGE,
    KC_EMAIL,
    KC_URL,
    KC_TWITTER,
    KC_BALUS
};
#define NAME    "swan_match"
#define EMAIL   "swan_match@yahoo.co.jp"
#define URL     "https://royal-keyboard-works.square.site/"
#define TWITTER "https://twitter.com/swan_match"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        RGB_RMOD,                LCTL(KC_A), LCTL(KC_S),    RGB_MOD,
        LT(_RAISE, KC_BSPC),     LCTL(KC_Z), LCTL(KC_Y),    LT(_LOWER, KC_DEL)
    ),
    [_RAISE] = LAYOUT(
        _______,                 KC_NAME, KC_EMAIL,         _______,
        _______,                 KC_URL,  KC_TWITTER,       MO(_ADJUST)
    ),
    [_LOWER] = LAYOUT(
        RGB_TOG,                 RGB_SAI, RGB_HUI,          _______,
        MO(_ADJUST),             RGB_SAD, RGB_HUD,          _______
    ),
    [_ADJUST] = LAYOUT(
        _______,                 RGB_VAI,  QK_REBOOT,       KC_BALUS,
        _______,                 RGB_VAD,  QK_REBOOT,    _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_NAME:
            if (record->event.pressed) {
                SEND_STRING(NAME);
            }
            break;
        case KC_EMAIL:
            if (record->event.pressed) {
                SEND_STRING(EMAIL);
            }
            break;
        case KC_URL:
            if (record->event.pressed) {
                SEND_STRING(URL);
            }
            break;
        case KC_TWITTER:
            if (record->event.pressed) {
                SEND_STRING(TWITTER);
            }
            break;
        case KC_BALUS:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_A));
                tap_code(KC_DEL);
                tap_code16(LCTL(KC_S));
            }
            break;
    }
    return true;
}
