/* Copyright 2019 %YOUR_NAME%
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
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include QMK_KEYBOARD_H
extern keymap_config_t keymap_config;
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
rgblight_config_t RGB_current_config;
#endif

#ifdef SSD1306OLED
  #include "ssd1306.h"
  #include <string.h>
  #include "print.h"
  #include "common/glcdfont.c"
  #include "sendchar.h"
  #include "common/oled_helper.h"
#endif
// Defines the keycodes used by our macros in process_record_user
//enum custom_keycodes {
//};

enum layer_number {
  _CTL = 0,
  _CURSOL,
  _MOUSE
};

#define CTL    TO(_CTL)
#define CURSOL TO(_CURSOL)
#define MOUSE  TO(_MOUSE)
#define CP     M(0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_CTL] = LAYOUT( \
    C(KC_Z), CURSOL,  C(KC_Y),      \
             C(KC_S),            \
    C(KC_C), RGB_MOD, C(KC_V) \
  ),

  [_CURSOL] = LAYOUT( \
    KC_ENT,  MOUSE,   KC_TAB,  \
             KC_UP,            \
    KC_LEFT, KC_DOWN, KC_RIGHT \
  ),

  [_MOUSE] = LAYOUT( \
    KC_MS_BTN1, CTL,        KC_MS_BTN2, \
                KC_MS_UP,               \
    KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT \
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
//float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
//float tone_plover[][2]     = SONG(PLOVER_SOUND);
//float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CTL:
      #ifdef AUDIO_ENABLE
        PLAY_SONG(tone_qwerty);
      #endif
      return true;
      break;
    case CURSOL:
      #ifdef AUDIO_ENABLE
        PLAY_SONG(tone_dvorak);
      #endif
      return true;
      break;
    case MOUSE:
      #ifdef AUDIO_ENABLE
        PLAY_SONG(music_scale);
      #endif
      return true;
      break;
    }
  return true;
}

void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
    startup_user();
  #endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    iota_gfx_init(true);   // turns on the display
  #endif
}

void led_set_user(uint8_t usb_led) {
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(50); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}
#endif

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

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
#define L_CTL 0
#define L_CURSOL (1<<_CURSOL)
#define L_MOUSE (1<<_MOUSE)

void render_status(struct CharacterMatrix *matrix) {
  render_logo(matrix);
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf, sizeof(buf), "Undef-%ld", layer_state);
  switch (layer_state) {
     case L_CTL:
      matrix_write_P(matrix, PSTR("Control Mode\n"));
      break;
    case L_CURSOL:
      matrix_write_P(matrix, PSTR("Cursol Mode\n"));
      break;
    case L_MOUSE:
      matrix_write_P(matrix, PSTR("Mouse Mode\n"));
      break;
    default:
      break;
      matrix_write(matrix, buf);
  }
  UPDATE_LED_STATUS();
  RENDER_LED_STATUS(matrix);
  // Host Keyboard LED Status
  //char led[40];
  //snprintf(led, sizeof(led), "\n%s  %s  %s", (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ", (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) ? "CAPS" : "    ", (host_keyboard_leds() & (1 << USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  //matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  render_status(&matrix);
  matrix_update(&display, &matrix);
}

#endif