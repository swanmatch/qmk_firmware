/* Copyright 2018 ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
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
enum layer {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE,
};

#define LOWER  LT(_LOWER, KC_ESC)
#define RAISE  LT(_RAISE, KC_TAB)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   :  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   -  |
 * `-------------+------+------+------|           |------+------+------+------+------'
                 | BsAlt| SpSft|EscLow|           |TabRas|EntCtl| DelOs|
 *               `--------------------'           `--------------------'
 */
  [_QWERTY] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_MINS,
      LALT_T(KC_BSPC), LSFT_T(KC_SPC), LOWER,         RAISE, LCTL_T(KC_ENT), GUI_T(KC_DEL)
  ),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   /  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   @  |   #  |   $  |   %  |   [  |           |   ]  |   4  |   5  |   6  |   +  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   `  |   &  |   *  |   !  |   {  |           |   }  |   1  |   2  |   3  |   =  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      |      | **** |           |ADJUST|   0  |   .  |
 *               `--------------------'           `--------------------'
 */
  [_LOWER] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_SLSH,
    KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LBRC,     KC_RBRC, KC_4,    KC_5,    KC_6,    KC_PPLS,
    KC_CIRC, KC_AMPR, KC_ASTR, KC_EXLM, KC_LCBR,     KC_RCBR, KC_1,    KC_2,    KC_3,    KC_PEQL,
                      _______, _______, _______,     ADJUST,  KC_0,    KC_DOT
  ),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  | PgUp |  F4  |  F5  |           |  F6  |  F7  |  UP  |  F9  | F10  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   ~  | HOME | PgDw |  END |  (   |           |   )  | Left | Down | Right|  |   |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   `  |      |  F3  |      |  '   |           |   "  | F11  |  F8  | F12  |  \   |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      |  ?   |ADJUST|           | **** |      |      |
 *               `--------------------'           `--------------------'
 */
  [_RAISE] = LAYOUT(
    KC_F1,   KC_F2,   KC_PGUP, KC_F4,   KC_5,        KC_F6,   KC_F7,   KC_UP,   KC_F9,   KC_F10,
    KC_TILD, KC_HOME, KC_PGDN, KC_END,  KC_LPRN,     KC_RPRN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PIPE,
    KC_GRV,  _______, KC_F3,   _______, KC_QUOT,     KC_DQUO, KC_F11,  KC_F8,   KC_F12,  KC_PEQL,
                      _______, KC_QUES, ADJUST,      _______, _______, _______
  ),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * | RESET|      |      |      |PrtSc |           |RGBTOG|      |      |      |RGBRST|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           | SpUp | EfFw | HueUp| SatUp| ValUp|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Reset|      |      |      |      |           | SpDw | EfRv | HueDw| SatDw| ValDw|
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      |      | **** |           | **** |      |      |
 *               `--------------------'           `--------------------'
 */
  [_ADJUST] =  LAYOUT(
    RESET,   XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,      RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, RGB_RST,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      RGB_SPI, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      RGB_SPD, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD,
                      _______, _______, _______,      _______,  _______, _______
  )
};

#ifdef RGBLIGHT_ENABLE

extern rgblight_config_t rgblight_config;

int  RGB_current_mode;

void matrix_init_user(void) {
  RGB_current_mode = rgblight_config.mode;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SCLN:
      if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
        if (record->event.pressed) {
          unregister_code(KC_LSFT);
          tap_code16(keycode);
          register_code(KC_LSFT);
        }
        /* else if (keyboard_report->mods & MOD_BIT(KC_RSFT)) {
          if (record->event.pressed) {
            unregister_code(KC_RSFT);
            tap_code16(keycode);
            register_code(KC_RSFT);
 	        }
        } */
      } else {
        if (record->event.pressed) {
          tap_code16(S(keycode));
        }
      }
      return false;
      break;
#ifdef RGBLIGHT_ENABLE
    case RGB_RST:
      if (record->event.pressed) {
        rgblight_enable();
        eeconfig_update_rgblight_default();
        RGB_current_mode = rgblight_config.mode;
      }
      return false;
      break;
#endif
  }
  return true;
}
