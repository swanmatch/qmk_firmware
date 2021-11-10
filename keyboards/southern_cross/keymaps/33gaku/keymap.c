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
#include "keymap_jp.h"       // qmk_firmware-master/quantum/keymap_extras/keymap_jp.h 日本語キーボード設定用
#include <sendstring_jis.h>

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RAISE,
    _LOWER,
    _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    KC_SSID = SAFE_RANGE,
    KC_PASS,
    KC_EMAIL,
    KC_URL,
    KC_TWITTER,
    KC_FACEBOOK,
    KC_ADDRESS,
    KC_TEL,
    KC_BALUS
};
#define SSID    "33gaku_wa"
#define PASS    "ugak33#W"
#define EMAIL   "info@33gaku.jp\n"
#define URL     "https://33gaku.jp/\n"
#define TWITTER "https://twitter.com/_33gaku\n"
#define FACEBOOK "https://www.facebook.com/33gaku/\n"
#define ADDRESS "naganoken matsumotoshi oote 3-3-9\n NTT\nhigashinihondaimyoutyoubiru 1F\n"
#define TEL     "0263-33-0339"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        RGB_RMOD,                KC_SSID,    KC_PASS,       RGB_MOD,
        LT(_RAISE, KC_BSPC),     KC_URL,     KC_EMAIL,      LT(_LOWER, KC_DEL)
    ),
    [_RAISE] = LAYOUT(
        _______,                 KC_ADDRESS, KC_TEL,        _______,
        _______,                 KC_TWITTER, KC_FACEBOOK,   MO(_ADJUST)
    ),
    [_LOWER] = LAYOUT(
        RGB_TOG,                 RGB_SAI,  RGB_HUI,         _______,
        MO(_ADJUST),             RGB_SAD,  RGB_HUD,         _______
    ),
    [_ADJUST] = LAYOUT(
        _______,                 RGB_VAI,  RESET,           KC_BALUS,
        _______,                 RGB_VAD,  EEPROM_RESET,    _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SSID:
            if (record->event.pressed) {
                SEND_STRING(SSID);
            }
            break;
        case KC_PASS:
            if (record->event.pressed) {
                SEND_STRING(PASS);
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
        case KC_FACEBOOK:
            if (record->event.pressed) {
                SEND_STRING(TWITTER);
            }
            break;
        case KC_ADDRESS:
            if (record->event.pressed) {
                SEND_STRING(ADDRESS);
            }
            break;
        case KC_TEL:
            if (record->event.pressed) {
                SEND_STRING(TEL);
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
