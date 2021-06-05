#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  KC_00,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                register_code(KC_LSFT);
                register_code(KC_SCLN);
                unregister_code(KC_9);
                register_code(KC_SCLN);
            case 1:
                return MACRO(T(CAPS), T(QUOT), T(CAPS));
        }
    }
    return MACRO_NONE;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
  /* Qwerty
   * ,-----------------------------------------.-----------------------------------------.
   * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  =   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |ADJUST|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   :  |  "   |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  /   |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctr  |  OS  | Alt  | Bksp |Space | Calc | F12  |Cursol| Del  | Enter|   [  |   ]  |
   * `-----------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,          KC_3,    KC_4,           KC_5,  KC_6,   KC_7,  KC_8,    KC_9,           KC_0,    KC_BSLS, \
    KC_TAB,  KC_Q,    KC_W,          KC_E,    KC_R,           KC_T,  KC_Y,   KC_U,  KC_I,    KC_O,           KC_P,    KC_EQL,  \
    ADJUST,  KC_A,    KC_S,          KC_D,    KC_F,           KC_G,  KC_H,   KC_J,  KC_K,    KC_L,           KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,          KC_C,    KC_V,           KC_B,  KC_N,   KC_M,  KC_COMM, KC_DOT,         KC_SLSH, KC_MINS, \
    KC_LCTL, KC_LGUI, LALT_T(KC_F5), KC_BSPC, RSFT_T(KC_SPC), LT(2,KC_ESC), KC_F12, LT(1,KC_TAB), KC_DEL,  RCTL_T(KC_ENT), KC_LBRC, KC_RBRC  \
  ),
  /* Cursol
   * ,-----------------------------------------------------------------------------------.
   * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  |PrtSc |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      | NmLk | ScLk | PgUp |Pouse |      |      |      |  Up  |      |      | F12  |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      | Ins  | Home | PgDw | End  |  <   |  >   | Left | Down |Right |      | F11  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | Undo | Cut  | Copy |Paste |  (   |  )   | OSL  | OSDw | OSR  |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,        KC_F8,        KC_F9,        KC_F10,  KC_PSCR, \
    _______, KC_NLCK, KC_SLCK, KC_PGUP, KC_PAUS, _______, _______, _______,      KC_UP,        _______,      _______, KC_F12,  \
    _______, KC_INS,  KC_HOME, KC_PGDN, KC_END,  KC_LT,   KC_GT,   KC_LEFT,      KC_DOWN,      KC_RGHT,      _______, KC_F11,  \
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_LPRN, KC_RPRN, LCA(KC_LEFT), LCA(KC_DOWN), LCA(KC_RGHT), _______, _______, \
    KC_LCTL, _______, _______, _______, _______, ADJUST,  _______, _______,      _______,      _______,      KC_LPRN, KC_RPRN \
  ),
  /* Calc
   * 
   * ,-----------------------------------------------------------------------------------.
   * |  ~   |      |      |      |      |      |      | NumLk|  /   |  *   |  -   |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  +   |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |  @   |  #   |  $   |  %   |  {   |  }   |  4   |  5   |  6   |  ,   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |  ^   |  &   |  *   |  !   |  [   |  ]   |  1   |  2   |  3   |  =   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  0   |  00  |  .   |Enter |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
    KC_TILD, _______, _______,  _______,  _______, _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, _______, \
    _______, KC_1,    KC_2,     KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_PPLS, _______, \
    _______, KC_AT,   KC_HASH,  KC_DLR,   KC_PERC, KC_LCBR, KC_RCBR, KC_4,    KC_5,    KC_6,    KC_PCMM, _______, \
    _______, KC_CIRC, KC_AMPR,  KC_ASTR,  KC_EXLM, KC_LBRC, KC_RBRC, KC_1,    KC_2,    KC_3,    KC_PEQL, _______, \
    _______, _______, _______,  _______,  _______, _______, ADJUST, KC_0,    KC_00,   KC_PDOT, KC_PENT, _______  \
  ),

  /* Adjust
   * ,-----------------------------------------.-----------------------------------------.
   * |RESET |      |      |      |      |      |      |      |      |      |      |DEBUG |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |      |      |HueUp |      |      |      |SpdDw |BriUp |SpdUp |      |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |      |SadUp |HueDw |SadDw |      |      |ModeDw|BriDw |ModeUp|      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |LEDRST|      |      |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
    RESET,   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, DEBUG,   \
    RGBRST,  _______, _______, RGB_HUI, _______, _______, _______, RGB_SPD,  RGB_VAI, RGB_SPI, _______, _______, \
    _______, _______, RGB_SAD, RGB_HUD, RGB_SAI, _______, _______, RGB_RMOD, RGB_VAD, RGB_MOD, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, \
    _______, _______, _______, _______, _______,  RGBRST, _______, _______,  _______, _______, _______, _______  \
  )
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          rgblight_mode(14);
        }
      #endif
      break;
    case KC_SCLN:
      if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
        if (record->event.pressed) {
          unregister_code(KC_LSFT);
          register_code(KC_SCLN);
          unregister_code(KC_SCLN);
          register_code(KC_LSFT);
        }
      } else if (keyboard_report->mods & MOD_BIT(KC_RSFT)) {
        if (record->event.pressed) {
          unregister_code(KC_RSFT);
          register_code(KC_SCLN);
          unregister_code(KC_SCLN);
          register_code(KC_RSFT);
        }
      } else {
        if (record->event.pressed) {
          register_code(KC_LSFT);
          register_code(KC_SCLN);
          unregister_code(KC_SCLN);
          unregister_code(KC_LSFT);
        }
      }
      return false;
      break;
    case KC_QUOT:
      if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
        if (record->event.pressed) {
          unregister_code(KC_LSFT);
          register_code(KC_QUOT);
          unregister_code(KC_QUOT);
          register_code(KC_LSFT);
        }
      } else if (keyboard_report->mods & MOD_BIT(KC_RSFT)) {
        if (record->event.pressed) {
          unregister_code(KC_RSFT);
          register_code(KC_QUOT);
          unregister_code(KC_QUOT);
          register_code(KC_RSFT);
        }
      } else {
        if (record->event.pressed) {
          register_code(KC_LSFT);
          register_code(KC_QUOT);
          unregister_code(KC_QUOT);
          unregister_code(KC_LSFT);
        }
      }
      return false;
      break;
    case KC_00:
      if (record->event.pressed) {
        SEND_STRING("00");
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}
