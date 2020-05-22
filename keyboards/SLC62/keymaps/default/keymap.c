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
    _NUM,
    _ADJUST
};

#define ESC   LT(_NUM,    KC_ESC )
#define ENT   LT(_ADJUST, KC_ENT )
#define MUTE1 LT(_RAISE,  KC_MUTE)
#define MUTE2 LT(_LOWER,  KC_MUTE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = {
        { KC_NO,    KC_NO,    ESC,      ENT     },
        { KC_NO,    KC_NO,    MUTE1,    MUTE2   },
        { KC_A,     KC_B,     KC_C,     KC_D    },
        { KC_E,     KC_F,     KC_G,     KC_H    }
    },
    [_RAISE] = {
        { KC_NO,    KC_NO,    KC_TAB,   KC_SPC  },
        { KC_NO,    KC_NO,    _______,  KC_I    },
        { KC_J,     KC_K,     KC_L,     KC_M    },
        { KC_N,     KC_O,     KC_P,     KC_R    }
    },
    [_LOWER] = {
        { KC_NO,    KC_NO,    KC_BSPC,  KC_DEL  },
        { KC_NO,    KC_NO,    KC_R,     _______ },
        { KC_S,     KC_T,     KC_U,     KC_V    },
        { KC_W,     KC_X,     KC_Y,     KC_Z    }
    },
    [_NUM] = {
        { KC_NO,    KC_NO,    _______,  KC_NO   },
        { KC_NO,    KC_NO,    KC_0,     KC_1    },
        { KC_2,     KC_3,     KC_4,     KC_5    },
        { KC_6,     KC_7,     KC_8,     KC_9    }
    },
    [_ADJUST] = {
        { KC_NO,    KC_NO,    AU_TOG,   _______  },
        { KC_NO,    KC_NO,    RGB_MOD,  RGB_RMOD },
        { RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI  },
        { RGB_RMOD, RGB_HUD,  RGB_SAD,  RGB_VAD  }
    }
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* left encoder */
    if (layer_state == (1<<_ADJUST)) {
      if (clockwise) {
        tap_code(KC_UP);
      } else {
        tap_code(KC_DOWN);
      }
    } else {
      if (clockwise) {
        tap_code(KC_WH_U);
      } else {
        tap_code(KC_WH_D);
      }
    }
  } else if (index == 1) { /* right encoder */
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
  }
}

void set_state_to_led(uint8_t at) {
    for(uint8_t i = 2; i < 12; i++) {
        if (i == at) {
            sethsv(
                rgblight_get_hue(),
                rgblight_get_sat(),
                rgblight_get_val(),
                (LED_TYPE *)&led[i]
            );
        } else {
            sethsv(
                0,
                0,
                0,
                (LED_TYPE *)&led[i]
            );
        }
    }
    rgblight_set();
}

void keyboard_pre_init_user(void) {
    rgblight_set_effect_range(0, 2);
}
void keyboard_post_init_user(void) {
    set_state_to_led(5);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        //case keymaps[_BASE][3][0]:
        case KC_A:
            if (record->event.pressed) {
                set_state_to_led(5);
            }
            break;
        case KC_B:
            if (record->event.pressed) {
                set_state_to_led(4);
            }
            break;
        case KC_C:
            if (record->event.pressed) {
                set_state_to_led(3);
            }
            break;
        case KC_D:
            if (record->event.pressed) {
                set_state_to_led(2);
            }
            break;
        case KC_E:
            if (record->event.pressed) {
                set_state_to_led(6);
            }
            break;
        case KC_F:
            if (record->event.pressed) {
                set_state_to_led(7);
            }
            break;
        case KC_G:
            if (record->event.pressed) {
                set_state_to_led(8);
            }
            break;
        case KC_H:
            if (record->event.pressed) {
                set_state_to_led(9);
            }
            break;
        case KC_I:
            if (record->event.pressed) {
                set_state_to_led(10);
            }
            break;
        case KC_MUTE:
        //case MUTE1:
        //case MUTE2:
            //if (record->event.pressed) {
                rgblight_toggle();
            //}
            break;
    }
    return true;
}
/*

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
