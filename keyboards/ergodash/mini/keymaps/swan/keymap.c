#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  KC_00,
};
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define CALC LT(2, KC_ESC)
#define CUSL LT(1, KC_TAB)
#define ADJUST LT(3, KC_SPC)
#define REVERSE(kc) \
case kc: \
  if (keyboard_report->mods & MOD_BIT(KC_LSFT)) { \
    if (record->event.pressed) { \
      unregister_code(KC_LSFT); \
      register_code(kc); \
      unregister_code(kc); \
      register_code(KC_LSFT); \
    } \
/*  } else if (keyboard_report->mods & MOD_BIT(KC_RSFT)) { \
    if (record->event.pressed) { \
      unregister_code(KC_RSFT); \
      register_code(kc); \
      unregister_code(kc); \
      register_code(KC_RSFT);
    } */ \
  } else { \
    if (record->event.pressed) { \
      register_code(KC_LSFT); \
      register_code(kc); \
      unregister_code(kc); \
      unregister_code(KC_LSFT); \
  } \
  } \
  return false; \
  break;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  Esc |   Q  |   W  |   E  |   R  |   T  |   -  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |   [  |                    |   ]  |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | Space|                    | Enter|   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Left | Down |  Up  | Right|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_Q,    KC_W,    KC_E,          KC_R,    KC_T,           KC_LPRN,  KC_RPRN, KC_Y,          KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_TAB,  KC_A,    KC_S,    KC_D,          KC_F,    KC_G,           KC_LBRC,  KC_RBRC, KC_H,          KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,          KC_V,    KC_B,           KC_NO ,   KC_NO ,  KC_N,          KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    KC_LCTL, KC_NO,   KC_LGUI, LALT_T(KC_F5), KC_BSPC, LSFT_T(KC_SPC), CALC,     CUSL,    LCTL_T(KC_ENT), KC_DEL, KC_F12,  KC_APP,  KC_QUES, KC_PERC  \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |   `  |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |   ~  |   1  |   2  |   3  |   4  |   5  |   {  |                    |   }  | Left | Down |  Up  | Right|   :  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   6  |   7  |   8  |   9  |   0  | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
  _______, KC_F1,   KC_F2,      KC_PGUP, KC_F4,      KC_F5,   _______,    _______, KC_F6,   KC_F7,        KC_UP,   KC_F9,        KC_F10,  KC_PSCR, \
  _______, KC_TILD, KC_HOME,    KC_PGDN, KC_END,     KC_LCBR, _______,    _______, KC_RCBR, KC_LEFT,      KC_DOWN, KC_RGHT,      KC_PIPE, KC_F11,  \
  _______, KC_GRV,  C(KC_LEFT), KC_F3,   C(KC_RGHT), KC_LPRN, _______,    _______, KC_RPRN, LCA(KC_LEFT), KC_F8,   LCA(KC_RGHT), KC_BSLS, _______, \
  _______, _______, _______,    _______, _______,    _______, ADJUST,     _______, _______, _______,      _______, _______,      _______, _______  \
  ),

  /* Raise
  * ,----------------------------------------------------------------------------------------------------------------------.
  * |   `  |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
  * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
  * |   ~  |   F1 |   F2 |   F3 |   F4 |   F5 |   {  |                    |   }  | Left | Down |  Up  | Right|   :  |  "   |
  * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
  * | Shift|   F6 |   F7 |   F8 |   F9 |  F10 | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
  * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
  * | Ctrl |  F11 |  F12 | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
  * ,----------------------------------------------------------------------------------------------------------------------.
  */
  [_RAISE] = LAYOUT(
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,     _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_PPLS, _______, \
  _______, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LT,   _______,     _______, KC_GT,   KC_4,    KC_5,    KC_6,    KC_TILD, _______, \
  _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_EXLM, KC_LBRC, _______,     _______, KC_RBRC, KC_1,    KC_2,    KC_3,    KC_PEQL, _______, \
  _______, _______, _______, _______, _______, _______, _______,     ADJUST,  _______, _______, _______, _______, _______, _______  \
    ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, BL_INC,  XXXXXXX, XXXXXXX, _______,   _______, XXXXXXX, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, \
  XXXXXXX, BL_TOGG, BL_BRTG, BL_DEC,  XXXXXXX, XXXXXXX, _______,   _______, RGB_TOG, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,  _______, _______, _______, _______  \
  )
};
