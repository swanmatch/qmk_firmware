/* Copyright 2022 swanmatch
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
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   /* Qwerty
     * ,-----------------------------------------.                ,-------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                |   Y  |   U  |   I  |   O  |   P  |    [   |
     * |------+------+------+------+------+------|                |------+------+------+------+------+--------|
     * | Shift|   A  |   S  |   D  |   F  |   G  |                |   H  |   J  |   K  |   L  |   -  |    ]   |
     * |------+------+------+------+------+------|                |------+------+------+------+------+--------|
     * |  Ctrl|   Z  |   X  |   C  |   V  |   B  |                |   N  |   M  |   ,  |   .  |   /  |    \   |
     * `-------------------------------------------------. ,--------------------------------------------------'
     *               | Ctrl | MHEN/Win | ENT/LOWER|  Bsp  | | Del | spc/RAISE |HENK/Alt| Shift|
     *               `------------------------------------' `-------------------------------'
     */
  [_QWERTY] = LAYOUT(
        KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T,                    KC_Y, KC_U, KC_I,    KC_O,   KC_P,      KC_LBRC,
        KC_LSFT,  KC_A, KC_S, KC_D, KC_F, KC_G,                    KC_H, KC_J, KC_K,    KC_L,   KC_MINS,   KC_RBRC,
        KC_LCTL,  KC_Z, KC_X, KC_C, KC_V, KC_B,                    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,   KC_BSLS,
     LGUI(KC_V),LGUI_T(KC_MHEN), LT(_LOWER, KC_ENT), KC_BSPC,     KC_DEL, LT(_RAISE, KC_SPC),ALT_T(KC_HENK),LCTL(KC_S)
  ),
    /* Lower
     * ,-----------------------------------------.                ,------------------------------------------.
     * |  Esc |   !  |   ?  |   [  |   ]  |   ~  |                |   6  |   7  |   8  |   9  |   *  |   /   |
     * |------+------+------+------+------+------|                |------+------+------+------+------+-------|
     * |   '  |   #  |   "  |   (  |   )  |   @  |                |      |   4  |   5  |   6  |   -  |   =   |
     * |------+------+------+------+------+------|                |------+------+------+------+------+-------|
     * |   ^  |   %  |   &  |   ;  |   :  |   |  |                |   0  |   1  |   2  |   3  |   +  |  Ent  |
     * `-------------------------------------------------. ,-------------------------------------------------'
     *                      |      |ZENHAN| LOWER|       | |      | RAISE|   .  |      |
     *                      `----------------------------' `---------------------------'
     */
  [_LOWER] = LAYOUT(
         KC_ESC, KC_EXLM,KC_QUES,  KC_LBRC,        KC_RBRC, KC_TILD,      KC_6,     KC_7,   KC_8,   KC_9, KC_ASTR, KC_SLSH,
        KC_QUOT, KC_HASH,KC_DQUO,  KC_LPRN,        KC_RPRN,   KC_AT,       KC_NO,     KC_4,   KC_5,   KC_6, KC_MINS, KC_EQL,
        KC_CIRC, KC_PERC,KC_AMPR,  KC_SCLN, SFT_T(KC_SCLN), KC_PIPE,      KC_0,     KC_1,   KC_2,   KC_3, KC_PLUS, KC_ENT,
                         _______,  KC_ZKHK,        _______, KC_TRNS,   _______,  _______, KC_DOT,  _______
  ),
    /* Raise
     * ,-----------------------------------------.                ,------------------------------------------.
     * | Esc  |   1  |   2  |   3  |   4  |   5  |                |  6   |      |  ��  |      |  PGUP|  Bsp  |
     * |------+------+------+------+------+------|                |------+------+------+------+------+-------|
     * |F11/Shift| F1|  F2  |  F3  |  F4  |  F5  |                |      |  ��  |  ��  |  ��  | Shift|  ENT  |
     * |------+------+------+------+------+------|                |------+------+------+------+------+-------|
     * |F12/Ctrl | F6|  F7  |  F8  |  F9  |  F10 |                |      |      |      |      |PGDOWN|       |
     * `------------------------------------------------. ,-------------------------------------------------'
     *                      |      |      | LOWER|      | |       |RAISE |      |      |
     *                      `---------------------------' `----------------------------'
     */

  [_RAISE] = LAYOUT(
          KC_ESC,  KC_1, KC_2,     KC_3,     KC_4,    KC_5,        KC_6,   KC_NO,   KC_UP,    KC_NO,  KC_PGUP, KC_BSPC,
   SFT_T(KC_F11), KC_F1, KC_F2,   KC_F3,    KC_F4,   KC_F5,       KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT,  KC_LSFT,  KC_ENT,
  LCTL_T(KC_F12), KC_F6, KC_F7,   KC_F8,    KC_F9,  KC_F10,       KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_PGDN,   KC_NO,
                      _______, KC_LGUI,  _______, _______,     _______, _______, KC_LALT,  _______
  ),

    /* Adjust
     * ,-----------------------------------------.                ,------------------------------------------.
     * |  Esc |   1  |   2  |   3  |   4  |   5  |                |   6  |   7  |   8  |   9  |   0  |  Del  |
     * |------+------+--------+------+--------+--|                |------+------+------+------+------+-------|
     * |F11/Shift| F1|  F2  |  F3  |  F4  |  F5  |                | LTOG | LMOD |      | C A D| A Prt| PrtScn|
     * |------+------+--------+------+--------+--|                |------+------+------+------+------+-------|
     * |F12/Ctrl | F6|  F7  |  F8  |  F9  |  F10 |                |  VAD |  VAI |  HUD |  HUI |  SAD |  SAI  |
     * `------------------------------------------------. ,-------------------------------------------------'
     *                      |      |      | LOWER|      | |       | RAISE|      |      |
     *                      `---------------------------' `----------------------------'
     */

  [_ADJUST] = LAYOUT(
          KC_ESC,  KC_1,  KC_2,  KC_3,   KC_4,   KC_5,          KC_6,    KC_7,    KC_8,        KC_9,          KC_0,  KC_DEL,
   SFT_T(KC_F11), KC_F1, KC_F2, KC_F3,  KC_F4,  KC_F5,       RGB_TOG, RGB_MOD,   KC_NO, LCA(KC_DEL), LALT(KC_PSCR), KC_PSCR,
  LCTL_T(KC_F12), KC_F6, KC_F7, KC_F8,  KC_F9, KC_F10,       RGB_VAD, RGB_VAI, RGB_HUD,     RGB_HUI,       RGB_SAD, RGB_SAI,
                     _______,_______,_______,_______,       _______, _______, _______,  _______
   )
};

