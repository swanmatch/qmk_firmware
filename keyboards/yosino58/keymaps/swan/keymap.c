#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
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
/* QWERTY
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                                  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                                  |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |                                  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------.-------.  ,---------------|   N  |   M  |   ,  |   .  |   /  |  -   |
 * `-----------------------------------------/   [   /       /   \       \  ]   \----------------------------------------'
 *                          | Alt  | Bksp | /-------/ Calc  /    \Cursol \-------\  | Del  |  App  |
 *                          |  F5  |      |/ CtrSp /  Esc  /       \ Tab  \ SftEn \ |      |  F12  |
 *                          `-----------------------------'         '------------------------------'
 */
 [_QWERTY] = LAYOUT( \
  KC_GESC,  KC_1, KC_2, KC_3, KC_4, KC_5,                                                KC_6,   KC_7,    KC_8,    KC_9,   KC_0,    KC_BSLS, \
  KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T,                                                KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    KC_EQL,  \
  KC_LSFT,  KC_A, KC_S, KC_D, KC_F, KC_G,                                                KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
  KC_LCTRL, KC_Z, KC_X, KC_C, KC_V, KC_B,    KC_LBRC,        CALC, CUSL, KC_RBRC,        KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS, \
                     LALT_T(KC_F5), KC_BSPC, LSFT_T(KC_SPC),             LCTL_T(KC_ENT), KC_DEL, GUI_T(KC_F12)\
  ),

/* Cursol
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  F1  |  F2  | PgUp |  F4  |  F5  |                                  |  F6  |  F7  |  Up  |  F9  | F10  |PrtSc |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  ~   | Home | PgDw | End  |  (   |                                  |  )   | Left | Down |Right | F8   | F11  |
 * |------+------+------+------+------+------+                                  +------+------+------+------+------+------|
 * |      |  `  | CLft |  F3  | CRgt |  (   |-------.-------.  ,---------------|  )   | OSL  |  F8  | OSR  |      |      |
 * `-----------------------------------------/   (   /       /   \       \  )   \----------------------------------------'
 *                          | LAlt | LGUI | /-------/       /     \       \-------\  |      |      |
 *                          |      |      |/ LOWER /       /       \       \       \ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_LOWER] = LAYOUT( \
  RESET,   KC_F1,   KC_F2,      KC_F3,   KC_F4,      KC_F5,                                        KC_F6,   KC_F7,        KC_F8,   KC_F9,        KC_F10,  RESET,   \
  RGBRST,  KC_F1,   KC_F2,      KC_PGUP, KC_F4,      KC_F5,                                        KC_F6,   KC_F7,        KC_UP,   KC_F9,        KC_F10,  RGBRST,  \
  _______, KC_TILD, KC_HOME,    KC_PGDN, KC_END,     KC_LPRN,                                      KC_RPRN, KC_LEFT,      KC_DOWN, KC_RGHT,      KC_PIPE, KC_F11,  \
  _______, KC_GRV,  C(KC_LEFT), KC_F3,   C(KC_RGHT), KC_LPRN, KC_LPRN,   ADJUST, _______, KC_RPRN, KC_RPRN, LCA(KC_LEFT), KC_F8,   LCA(KC_RGHT), KC_BSLS, KC_PSCR, \
                                         _______,    _______, C(KC_SPC),                  _______, _______, _______ \
  ),

/* Calculater
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |  ~   |      |      |      |      |      |                                  |      | NmLk |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  1   |  2   |  3   |  4   |  5   |                                  |  6   |  7   |  8   |  9   |  +   |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  @   |  #   |  $   |  %   |  [   |                                  |  ]   |  4   |  5   |  6   |  ~   |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  ^   |  &   |  *   |  !   |  {   |-------.-------.  ,---------------|  }   |  1   |  2   |  3   |  =   |      |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /-------/       /     \       \-------\  |      |      |
 *                          |      |      |/       /       /       \       \   0   \ |  00  |  .   |
 *                          `-----------------------------'         '------------------------------'
 */
 [_RAISE] = LAYOUT( \
  _______, _______, _______,  _______,  _______, _______,                                    _______, KC_NLCK, _______, _______, _______, _______, \
  _______, KC_1,    KC_2,     KC_3,     KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_PPLS, _______, \
  _______, KC_AT,   KC_HASH,  KC_DLR,   KC_PERC, KC_LBRC,                                    KC_RBRC, KC_4,    KC_5,    KC_6,    KC_TILD, _______, \
  _______, KC_CIRC, KC_AMPR,  KC_ASTR,  KC_EXLM, KC_LCBR, _______, _______, ADJUST, _______, KC_RCBR, KC_1,    KC_2,    KC_3,    KC_PEQL, _______, \
                                        _______, _______, _______,                  KC_0,    KC_00,   KC_PDOT \
  ),

/*   ADJUST
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |RESET |      |      |      |      |      |                                  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                  |      | SPD- | VAL+ | SPD+ |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                  |      | MOD- | VAL- | MOD+ |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.-------.  ,---------------|      |      |      |      |      |      |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /-------/       /     \       \-------\  |      |      |
 *                          |      |      |/       /       /       \       \       \ |      |      |
 *                          `-----------------------------'         '------------------------------'
*/

 [_ADJUST] = LAYOUT( \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     RGB_SPI, RGB_MOD,  RGB_VAI, RGB_SAI, RGB_HUI, _______, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     RGB_SPD, RGB_RMOD, RGB_VAD, RGB_SAD, RGB_HUD, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                      XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX \
  )
};


int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
      #ifdef SSD1306_128X64
        iota_gfx_init(false);   // turns on the display
      #else
        iota_gfx_init(!has_usb());   // turns on the display
      #endif
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

//assign the right code to your layers for OLED display
#define L_QWERTY 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    static char indctr[2][20][5]=
    {
      // white icon
      {
        {0x80,0x81,0x82,0x83,0},
        {0x88,0x89,0x8A,0x8B,0},
        {0x90,0x91,0x92,0x93,0},
        {0x98,0x99,0x9A,0x9B,0},
        {0x01,0x02,0x03,0x04,0},
        {0xA0,0xA1,0xA2,0xA3,0},
        {0xA8,0xA9,0xAA,0xAB,0},
        {0xB0,0xB1,0xB2,0xB3,0},
        {0xB8,0xB9,0xBA,0xBB,0},
        {0x21,0x22,0x23,0x24,0},
        {0xC0,0xC1,0xC2,0xC3,0},
        {0xC8,0xC9,0xCA,0xCB,0},
        {0xD0,0xD1,0xD2,0xD3,0},
        {0xD8,0xD9,0xDA,0xDB,0},
        {0x41,0x42,0x43,0x44,0},
        {0xE0,0xE1,0xE2,0xE3,0},
        {0xE8,0xE9,0xEA,0xEB,0},
        {0xF0,0xF1,0xF2,0xF3,0},
        {0xF8,0xF9,0xFA,0xFB,0},
        {0x61,0x62,0x63,0x64,0}
      },
      // Black icon
      {
        {0x84,0x85,0x86,0x87,0},
        {0x8C,0x8D,0x8E,0x8F,0},
        {0x94,0x95,0x96,0x97,0},
        {0x9C,0x9D,0x9E,0x9F,0},
        {0x05,0x06,0x07,0x08,0},
        {0xA4,0xA5,0xA6,0xA7,0},
        {0xAC,0xAD,0xAE,0xAF,0},
        {0xB4,0xB5,0xB6,0xB7,0},
        {0xBC,0xBD,0xBE,0xBF,0},
        {0x25,0x26,0x27,0x28,0},
        {0xC4,0xC5,0xC6,0xC7,0},
        {0xCC,0xCD,0xCE,0xCF,0},
        {0xD4,0xD5,0xD6,0xD7,0},
        {0xDC,0xDD,0xDE,0xDF,0},
        {0x45,0x46,0x47,0x48,0},
        {0xE4,0xE5,0xE6,0xE7,0},
        {0xEC,0xED,0xEE,0xEF,0},
        {0xF4,0xF5,0xF6,0xF7,0},
        {0xFC,0xFD,0xFE,0xFF,0},
        {0x65,0x66,0x67,0x68,0}
      }
    };

    int rown = 0;
    int rowc = 0;
    int rowl = 0;
    int rowr = 0;
    int rowa = 0;

    //Set Indicator icon
    if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) { rown = 1; } else { rown = 0; }
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { rowc = 1; } else { rowc = 0; }
    if (layer_state == L_LOWER) { rowl = 1; }
    if (layer_state == L_RAISE) { rowr = 1; }
    if (layer_state == L_ADJUST) { rowa = 1; }

    matrix_write(matrix, indctr[rowl]  [0]);
    matrix_write(matrix, indctr[rowr]  [1]);
    matrix_write(matrix, indctr[rowa]  [2]);
    matrix_write(matrix, indctr[rowc]  [3]);
    matrix_write(matrix, indctr[rown]  [4]);
    matrix_write_char(matrix, 0x13);
    matrix_write(matrix, indctr[rowl]  [5]);
    matrix_write(matrix, indctr[rowr]  [6]);
    matrix_write(matrix, indctr[rowa]  [7]);
    matrix_write(matrix, indctr[rowc]  [8]);
    matrix_write(matrix, indctr[rown]  [9]);
    matrix_write_char(matrix, 0x13);
    matrix_write(matrix, indctr[rowl]  [10]);
    matrix_write(matrix, indctr[rowr]  [11]);
    matrix_write(matrix, indctr[rowa]  [12]);
    matrix_write(matrix, indctr[rowc]  [13]);
    matrix_write(matrix, indctr[rown]  [14]);
    matrix_write_char(matrix, 0x13);
    matrix_write(matrix, indctr[rowl]  [15]);
    matrix_write(matrix, indctr[rowr]  [16]);
    matrix_write(matrix, indctr[rowa]  [17]);
    matrix_write(matrix, indctr[rowc]  [18]);
    matrix_write(matrix, indctr[rown]  [19]);

  }else{
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);  
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    REVERSE(KC_SCLN)
    REVERSE(KC_QUOT)
    case KC_00:
      if (record->event.pressed) {
        SEND_STRING("00");
      }
      return false;
      break;
  }
  return true;
}

