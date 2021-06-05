#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
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
  RGB_RIPPLE
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

#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  =   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Set  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |  /   |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctr  |  OS  | F12  | Alt  | Bksp |Space | Calc |Cursol|Enter | Del  |  Up  | Left | Down |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,          KC_3,    KC_4,           KC_5,    KC_6,    KC_7,           KC_8,    KC_9,    KC_0,    KC_BSLS, \
    KC_TAB,  KC_Q,    KC_W,          KC_E,    KC_R,           KC_T,    KC_Y,    KC_U,           KC_I,    KC_O,    KC_P,    KC_EQL,  \
    ADJUST,  KC_A,    KC_S,          KC_D,    KC_F,           KC_G,    KC_H,    KC_J,           KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,          KC_C,    KC_V,           KC_B,    KC_N,    KC_M,           KC_COMM, KC_DOT,  KC_SLSH, KC_MINS, \
    KC_LCTL, KC_LGUI, LALT_T(KC_F5), KC_BSPC, RSFT_T(KC_SPC), TT(2),   TT(1),   RCTL_T(KC_ENT), KC_DEL,  KC_F12,  KC_LBRC, KC_RBRC  \
  ),
  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  | F10  |PrtSc |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | NmLk | ScLk | PgUp |Pouse |      |             |      |      |  Up  |      |      | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Ins  | Home | PgDw | End  |      |             |      | Left | Down |Right |      | F11  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | Undo | Cut  | Copy |Paste |      |      |      |      | OSL  | OSDw | OSR  |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,        KC_F8,        KC_F9,        KC_F10,  KC_PSCR, \
    _______, KC_NLCK, KC_SLCK, KC_PGUP, KC_PAUS, _______, _______, _______,      KC_UP,        _______,      _______, KC_F12,  \
    _______, KC_INS,  KC_HOME, KC_PGDN, KC_END,  KC_LT,   KC_GT,   KC_LEFT,      KC_DOWN,      KC_RGHT,      _______, KC_F11,  \
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_LPRN, KC_RPRN, LCA(KC_LEFT), LCA(KC_DOWN), LCA(KC_RGHT), _______, _______, \
    KC_LCTL, _______, _______, _______, _______, _______, _______, _______,      _______,      _______,      KC_LPRN, KC_RPRN \
  ),
  /* Raise
   * 
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  1   |  2   |  3   |  4   |  5   |             |   6  |  7   |  8   |  9   |  +   |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |MusLft|MusDw |MusRgt|      |             |      |  4   |  5   |  6   |  ,   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |  1   |  2   |  3   |  =   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |  0   |  0   |  .   |Enter |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
    KC_TILD, _______, _______,  _______,  _______, _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, _______, \
    _______, KC_1,    KC_2,     KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_PPLS, _______, \
    _______, KC_AT,   KC_HASH,  KC_DLR,   KC_PERC, KC_LCBR, KC_RCBR, KC_4,    KC_5,    KC_6,    KC_PCMM, _______, \
    _______, KC_CIRC, KC_AMPR,  KC_ASTR,  KC_EXLM, KC_LBRC, KC_RBRC, KC_1,    KC_2,    KC_3,    KC_PEQL, _______, \
    _______, _______, _______,  _______,  _______, _______, _______, KC_0,    KC_00,   KC_PDOT, KC_PENT, _______  \
  ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  | F10  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |HueUp |      |      |             |      |SpdDw |BriUp |SpdUp |      | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |SadUp |HueDw |SadDw |      |             |      |ModeDw|BriDw |ModeUp|      | F11  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Ripple|      |      |      |      |      |Reset |LEDTgl|      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
    RESET,   _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, DEBUG,   \
    RGBRST,  _______, _______, RGB_HUI, _______, _______, _______, RGB_SPD,  RGB_VAI, RGB_SPI, _______, _______, \
    RGB_MOD, _______, RGB_SAD, RGB_HUD, RGB_SAI, _______, _______, RGB_RMOD, RGB_VAD, RGB_MOD, _______, _______, \
    RGB_MOD, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, \
    _______, RGBRST,  _______, _______, _______,  RGBRST, _______, _______,  _______, _______, _______, _______  \
  )
};
#else
#error "undefined keymaps"
#endif

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
    case RGB_RIPPLE:
//      if (record->event.pressed) {
//        ripple = true;
//      }
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
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(35);

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nMode: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Swan Match"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Calculator"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Cursor"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Setting"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
