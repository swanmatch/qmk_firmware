// Copyright (c) 2022 Takeshi Ishii (mtei@github)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FUNC,
    _ADJUST
};

#define KC_FUNC MO(_FUNC)
#define KC_ADJUST MO(_ADJUST)

#define LAYOUT_wrapper(...)    LAYOUT(__VA_ARGS__)

#define _1_2_3_4_5           KC_1, KC_2, KC_3, KC_4, KC_5
#define _6_7_8_9_0           KC_6, KC_7, KC_8, KC_9, KC_0

#define _Q_W_E_R_T           KC_Q, KC_W, KC_E, KC_R, KC_T
#define _Y_U_I_O_P           KC_Y, KC_U, KC_I, KC_O, KC_P
#define _A_S_D_F_G           KC_A, KC_S, KC_D, KC_F, KC_G
#define _H_J_K_L_SCLN        KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define _Z_X_C_V_B           KC_Z, KC_X, KC_C, KC_V, KC_B
#define _N_M_COMM_DOT_SLSH   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH

#define _NO_NO_NO           KC_NO, KC_NO, KC_NO
#define _ENG_NO_KANA        KC_LANG2, KC_NO, KC_LANG1

#define _F1_F2_F3_F4_F5     KC_F1, KC_F2, KC_F3, KC_F4, KC_F5
#define _F6_F7_F8_F9_F10    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10
#define _PS_SL              KC_PAUS, KC_SLCK
#define _SL_PS              KC_SLCK, KC_PAUS
#define _HOME__UP__PU_INS   KC_HOME, _______, KC_UP, _______, KC_PGUP, KC_INS
#define _INS_PU__UP__HOME   KC_INS, KC_PGUP, _______, KC_UP, _______, KC_HOME
#define _END_LEFT_DOWN_RIGHT_PD_DEL  KC_END, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_DEL
#define _DEL_PD_LEFT_DOWN_RIGHT_END  KC_DEL, KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END
#define ___  _______

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base
    [_BASE] = LAYOUT_wrapper(
      KC_PGUP, KC_ESC,   _1_2_3_4_5,       _ENG_NO_KANA,      _6_7_8_9_0,          KC_BSPC,
      KC_PGDN, KC_TAB,    _Q_W_E_R_T,  KC_MINS,     KC_EQL,  _Y_U_I_O_P,           KC_BSLS, KC_DEL,
               KC_LCTL,  _A_S_D_F_G,  KC_LBRC,       KC_RBRC, _H_J_K_L_SCLN,       KC_RCTL,
               KC_LSFT, _Z_X_C_V_B,  KC_GRV,  KC_NO,  KC_QUOT, _N_M_COMM_DOT_SLSH, KC_RSFT, KC_RSFT,
      KC_LALT, KC_FUNC,   KC_LGUI, KC_SPC, KC_BSPC,   KC_ENTER, KC_SPC, KC_RGUI,   KC_FUNC, KC_FUNC, KC_RALT
    ),
    // Func
    [_FUNC] = LAYOUT_wrapper(
      ___, ___, _F1_F2_F3_F4_F5,      ___, ___, ___,     _F6_F7_F8_F9_F10,  KC_F11,
      ___, ___, ___, _PS_SL, ___, ___, ___,    ___, ___, ___, _SL_PS,  ___, KC_F12, KC_F12,
           ___, _HOME__UP__PU_INS,                  _INS_PU__UP__HOME, ___,
           ___, _END_LEFT_DOWN_RIGHT_PD_DEL,  ___,  _DEL_PD_LEFT_DOWN_RIGHT_END, ___, ___,
      ___, ___,                ___, ___, ___,     ___, ___, ___,            ___, ___, ___
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

