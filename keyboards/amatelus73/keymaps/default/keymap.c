/* Copyright 2020 swanmatch
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

#define RAISE LT(_RAISE, KC_ESC)
#define LOWER LT(_LOWER, KC_TAB)
#define SPACE RSFT_T(KC_SPC)
#define ENTER RCTL_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base
    [_BASE] = LAYOUT(
      KC_PGUP, KC_ESC, KC_1,  KC_2,  KC_3,  KC_4,  KC_5, KC_MINS,   KC_HOME,   KC_EQL, KC_6,  KC_7,  KC_8,    KC_9,   KC_0,    KC_BSPC,
      KC_PGDN,  KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_LBRC,       KC_RBRC,  KC_Y,  KC_U,  KC_I,    KC_O,   KC_P,  KC_PIPE, KC_DEL,
              KC_CAPS,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_BSPC,         KC_QUOT,  KC_H,  KC_J,  KC_K,    KC_L,   KC_SCLN,    KC_ENT,
          KC_LSFT,     KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_LPRN, A(KC_F4), KC_RPRN,  KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_UP,  KC_RSFT,
      KC_PDOT, KC_RCTRL,           ALT_T(KC_BSPC), SPACE,   RAISE,           LOWER,   ENTER, KC_LGUI,                KC_LEFT, KC_DOWN, KC_RGHT
    ),
    // RAISE
    [_RAISE] = LAYOUT(
      _______,  RESET,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,          _______,  KC_6,    KC_7,   KC_8,   KC_9,   KC_0,  _______, _______,
              _______, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LBRC, _______,            _______,  KC_RBRC, KC_4,   KC_5,   KC_6,   KC_PPLS,  _______,
          _______,    KC_CIRC, KC_AMPR, KC_ASTR, KC_EXLM, KC_LCBR, _______,   _______,   _______,  KC_RCBR, KC_1,   KC_2,   KC_3,   KC_COMM, _______, _______,
      _______, _______,                          _______, _______, _______,              MO(_ADJUST), KC_0,  KC_PDOT,               _______, _______, _______
    ),
    // LOWER
    [_LOWER] = LAYOUT(
      _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______,  KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11,
      _______, _______, KC_F1,   KC_F2,   KC_PGUP, KC_F4,   KC_F5,   _______,          _______,  KC_F6,   KC_F7,   KC_UP,   KC_F9,  KC_F10, KC_F11, KC_F12,
              _______, KC_TILD, KC_HOME, KC_PGDN, KC_END,  KC_LBRC, _______,            _______,  KC_RBRC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PIPE,  _______,
          _______,    KC_GRV,  _______, KC_F3,   _______, _______, _______,   _______,   _______,  _______, _______, KC_F8,   _______, KC_BSLS, _______, _______,
      _______, _______,                      _______, _______, MO(_ADJUST),              _______, _______, _______,                    _______, _______, _______
    ),
    // ADJUST
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______,
              _______, _______, _______, MU_TOG,  CK_UP,   AU_TOG,  _______,            _______, RGB_SPI, RGB_MOD, RGB_VAI, RGB_SAI, RGB_HUI, _______,
          _______,    _______, _______, MU_MOD,  CK_DOWN, _______, _______,   _______,   _______, RGB_SPD, RGB_RMOD,RGB_VAD, RGB_SAD, RGB_HUD, _______, _______,
      _______, _______,                          _______, _______, _______,              _______, _______, _______,                   _______, _______, _______
    ),
};

