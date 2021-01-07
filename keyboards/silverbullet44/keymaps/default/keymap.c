/* Copyright 2019 SwanMatch
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
//enum custom_keycodes {
//  QMKBEST = SAFE_RANGE,
//  QMKURL
//};
enum layer {
    _QWERTY,
    _CURSOL,
    _CALC,
    _ADJUST,
};

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  KC_00,
  ALTAB
};
#define CALC LT(_CALC,   KC_ESC)
#define CUSL LT(_CURSOL, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                                  |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |Shift |   A  |   S  |   D  |   F  |   G  |                                  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  |-------.-------.  ,---------------|   N  |   M  |   ,  |   .  |   /  |  -   |
 * `-----------------------------------------/       /       /   \       \      \----------------------------------------'
 *                          | Alt  | Bksp | / Shift / Calc  /     \ Cursol\ Ctrl | Del  |  App  |
 *                          |  F5  |      |/ Space /  Esc  /       \  Tab  \ Enter\     |  F12  |
 *                          `-----------------------------'         '---------------------------'
 */
  [_QWERTY] = LAYOUT(
    KC_TAB,    KC_Q, KC_W, KC_E, KC_R, KC_T,                KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    KC_EQL,
    KC_LSFT,   KC_A, KC_S, KC_D, KC_F, KC_G,                KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LCTRL,  KC_Z, KC_X, KC_C, KC_V, KC_B,                KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
     LALT_T(KC_F5), KC_BSPC, LSFT_T(KC_SPC), CALC,    CUSL, LCTL_T(KC_ENT), KC_DEL, GUI_T(KC_F12)
  ),

/* Cursol
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |      |  F1  |  F2  | PgUp |  F4  |  F5  |                                  |  F6  |  F7  |  Up  |  F9  | F10  |PrtSc |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  ~   | Home | PgDw | End  |  (   |                                  |  )   | Left | Down |Right | F8   | F11  |
 * |------+------+------+------+------+------+                                  +------+------+------+------+------+------|
 * |      |  `   | CLft |  F3  | CRgt |SALTAB|-------.-------.  ,---------------|ALTTAB| OSL  |  F8  | OSR  |      |      |
 * `-----------------------------------------/       /       /   \       \      \----------------------------------------'
 *                          |      |      | /       /       /     \       \      \  |      |      |
 *                          |      |      |/       /       /       \       \      \ |      |      |
 *                          `-----------------------------'         '-----------------------------'
 */
  [_CURSOL] = LAYOUT(
  RESET ,  KC_F1,   KC_F2,      KC_PGUP, KC_F4,      KC_F5,                              KC_F6,   KC_F7,        KC_UP,   KC_F9,        KC_F10,  RESET,
  _______, KC_TILD, KC_HOME,    KC_PGDN, KC_END,     KC_LPRN,                            KC_RPRN, KC_LEFT,      KC_DOWN, KC_RGHT,      KC_PIPE, KC_F11,
  _______, KC_GRV,  C(KC_LEFT), KC_F3,   C(KC_RGHT), S(ALTAB),                           ALTAB,   LCA(KC_LEFT), KC_F8,   LCA(KC_RGHT), KC_BSLS, RGBRST,
                                _______,    _______, C(KC_SPC), MO(_ADJUST),    _______, _______, _______, _______
  ),

/* Calculater
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |      |  1   |  2   |  3   |  4   |  5   |                                  |  6   |  7   |  8   |  9   |  0   |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  @   |  #   |  $   |  %   |  [   |                                  |  ]   |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  ^   |  &   |  *   |  !   |  {   |-------.-------.  ,---------------|  }   |  1   |  2   |  3   |  =   |      |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /       /       /     \       \       \  |      |      |
 *                          |      |      |/       /       /       \       \   0   \ |  00  |  .   |
 *                          `-----------------------------'         '------------------------------'
 */
  [_CALC] = LAYOUT(
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LBRC,                        KC_RBRC, KC_4,    KC_5,    KC_6,    KC_PPLS, _______,
  _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_EXLM, KC_LCBR,                        KC_RCBR, KC_1,    KC_2,    KC_3,    KC_PEQL, _______,
                             _______, _______, _______, _______,   MO(_ADJUST), KC_0,    KC_00,   KC_PDOT
  ),

/*   ADJUST
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |      |      |      |FrqRst|      |      |                                  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |Music |FrqUp |Sound |      |                                  | SPD+ | MOD+ | VAL+ | SAD+ | HUE+ |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |Scale |FrqDwn|      |      |-------.-------.  ,---------------| SPD- | SPD- | VAL- | SAD- | HUE- |      |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /       /       /     \       \       \  |      |      |
 *                          |      |      |/       /       /       \       \       \ |      |      |
 *                          `-----------------------------'         '------------------------------'
*/

  [_ADJUST] = LAYOUT(
  _______, XXXXXXX, XXXXXXX, CK_RST,  XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX, XXXXXXX, MU_TOG,  CK_UP,   AU_TOG,  XXXXXXX,                      RGB_SPI, RGB_MOD,  RGB_VAI, RGB_SAI, RGB_HUI, XXXXXXX,
  XXXXXXX, XXXXXXX, MU_MOD,  CK_DOWN, XXXXXXX, XXXXXXX,                      RGB_SPD, RGB_RMOD, RGB_VAD, RGB_SAD, RGB_HUD, XXXXXXX,
                             XXXXXXX, XXXXXXX, XXXXXXX, _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX
  )
};

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

int  RGB_current_mode;
bool alt_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef RGBLIGHT_ENABLE
        case RGBRST:
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
            }
            break;
#endif
        case KC_SCLN:
            if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
                if (record->event.pressed) {
                    unregister_code(KC_LSFT);
                    tap_code16(keycode);
                    register_code(KC_LSFT);
                }
                /*  } else if (keyboard_report->mods & MOD_BIT(KC_RSFT)) {
                    if (record->event.pressed) {
                      unregister_code(KC_RSFT);
                      tap_code16(keycode);
                      register_code(KC_RSFT);
                    } */
            } else {
                if (record->event.pressed) {
                    tap_code16(S(keycode));
                }
            }
            return false;
            break;
        case KC_00:
            if (record->event.pressed) {
                tap_code(KC_0);
                register_code(KC_0);
            } else {
                unregister_code(KC_0);
            }
            return false;
            break;
        case S(ALTAB):
        case ALTAB:
            if (record->event.pressed) {
                if (!alt_pressed) {
                    alt_pressed = true;
                    register_code(KC_LALT);
                }
                if (keycode == S(ALTAB)) {
                    register_code(KC_LSFT);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
                if (keycode == S(ALTAB)) {
                    unregister_code(KC_LSFT);
                }
            }
            return false;
            break;
        default:
            if (alt_pressed) {
                alt_pressed = false;
                unregister_code(KC_LALT);
                if (record->event.pressed) {
                    return false;
                }
            }
            break;
    }
    return true;
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
}

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_makai_logo(void) {
    static const char PROGMEM makai_logo[] = {
        0,  0,  0,224,224,160,160,224,224,176,176, 48,160,160,224,224,160,160,  0,  0,  0,  0,224,224, 32, 32, 32,224,224, 32, 32, 32,224,224,  0,  0,  0,  0,128,240,112, 32, 96, 64, 32,224,224,  0,160,240,240,160,224,192,  0,  0,  0,224,224,176,176,224,224,  0,  0,224, 32, 32,224,224,128,192,  0,  0, 96,176,160,240,240,240,160,160,  0,  0,224,224,  0,240,240,  0,  0,  0,  0,  0,128,224,240, 32,  0,192,240,240,176,128,128,128,128,128,  0,  0, 32, 32, 32, 32, 32, 32, 32,  0,192,192,192, 96, 32, 48, 48, 32,  0,  0,
        0,  0,  0,255,255,  4,250,255,175,170,252,248,252,170,175,255,250,  4,  0,  0,  0, 64, 79, 47, 57,249,217, 15, 15, 25,249,249,111,111,192,128,  0,  0,131, 36,254,255,177,  0,  7,255,252, 12,166,255,255,166,167,  3,  0,  0, 38, 63,159,134,134,191,191,128,129,165,152,136,157,191, 55, 49,  0,  0, 64, 94, 70,223,223,223,230,126, 96,192, 67, 75, 88,255, 63,  0,  0,  8, 12,255,255,255,  0, 12,  7,  3,  1,255,255,255,136,136,136,  0,  0,  0,255,255,127, 17, 17, 63, 63,128,255,255, 31,  6,254,254,254,  6,  0,  0,
        0,  8, 14,  7,  1,  8, 12,  6,  3,  1,  0, 15, 15, 12, 15, 14, 15, 14, 12,  0,  0,  0,  8, 12,  7,  3,  0,  0,  0,  0, 15, 15,  0,  0,  0,  0,  0,  0, 12, 13,  7,  7,  2,  8,  6,  3,  6, 14, 12, 13, 13, 12, 12, 12,  0,  0,  8,  8, 15, 15,  8, 15, 15,  8, 15, 15,  8,  8, 15, 15,  8,  8,  0,  0,  0,  5, 13, 13, 15,  7,  4,  4,  0,  1,  3,  6, 15, 12,  8,  0,  0,  0,  0, 15, 15, 15,  0,  0,  0,  0,  0, 15, 15, 15,  0,  0,  0,  0,  0,  8, 15,  3,  0,  0,  0,  0, 12,  7,  3,  0,  0,  0, 15, 15, 15,  0,  0,  0,
    };
    oled_write_raw_P(makai_logo, sizeof(makai_logo));
}

static void render_status(void) {
    oled_write(" SilverBulletRequiem\n\n", false);

    oled_write("    ", false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write("QWERTY", false);
            break;
        case _CURSOL:
            oled_write("Cursol", false);
            break;
        case _CALC:
            oled_write("Number", false);
            break;
        case _ADJUST:
            oled_write("Adjust", false);
            break;
        default:
            oled_write("Undefined", false);
    }
    oled_write(" Layer\n", false);
    uint8_t modifiers = get_mods();
    led_t led_state = host_keyboard_led_state();
    oled_write("  ", false);
    oled_write("CapsLock", led_state.caps_lock);
    oled_write("  ", false);
    oled_write_ln("NumLock", led_state.num_lock);
    oled_write("  ", false);
    oled_write("Ctrl", (modifiers & MOD_MASK_CTRL));
    oled_write(" ", false);
    oled_write("Shift", (modifiers & MOD_MASK_SHIFT));
    oled_write(" ", false);
    oled_write("Alt", (modifiers & MOD_MASK_ALT));
    oled_write(" ", false);
    oled_write("OS", (modifiers & MOD_MASK_GUI));
}

static void render_logo(void) {
    static const char PROGMEM logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,124,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192, 96, 48, 24, 24, 12, 12,  6,  7, 62,242,131,  3,  3,  3,  3,  3,  3,  6,  6,  6,  4, 12, 24, 24, 48, 96,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,224,240,240,240,240,240,240,240,240, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224, 48,152,248, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,248, 30,  7,  3,  0,  0,  0,  0,128,224, 48, 24,  8,  4,  5, 31,250,130,  2,  2,  2,  6,  4, 12,  8, 16, 96,192,  0,  0,  0,128,129,135,142,248,224, 64, 96, 96, 32, 32, 48, 16, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 31, 63, 59,113,225,225,193,129,  3,  3,  3,129,224,240, 54,  2,  0,  0,224,248,254,255, 55, 13,  6,  1,  0,  0,240,252,248,  0,  0,128,224,224,128,  0,128,240,248,252,252,216,248, 48,  0,  0,  0,248,252,252,188,224, 48,248,240,128,  0,  0,  0,255,129,  0,  0,128,128,128,192,220,255, 64, 96, 32, 32, 48, 48, 16, 17, 31,252,200, 12, 12,  4,  4,  6,  2,  2,195,127,  1,  1,  1,  1,  0,  0,  0,255,127,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0, 48,124,126,115,112,112,112,121, 63, 31,  6,  0,  0, 15, 31, 31, 24,  8, 12,  7, 63, 63,127,127, 96, 48, 48, 24,  4, 15, 31, 31, 31, 28,  6,  3,  0,  0,  1,  1,  3, 15, 15, 28, 24, 25,  8, 12,  4,  6, 15, 31, 31, 15,  3,  0, 12,  4,  4,  6,  6,  2,  2,  3, 15, 61,113,193,128,  0,  0,  0,  0,  3,  4,  8, 16, 16, 32, 32, 32, 96, 96, 39,126,224, 48, 16,  8, 12,  6,  1,  0,  0,  0,  0,128,224,120, 31,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,224,224,224,224,240,240,224,224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,240, 56,216,120, 16,  0,  0,  0,129,227,247, 62,220,120, 24, 48, 48, 96, 96, 96, 96, 64, 64, 64, 64, 96, 99,254,240,240,240, 48, 24, 12, 12,  6,  3,129,192,224,224,128,  0,  0,  0,  0,128,192,224,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,225,249,255,247,113,112,120,120,232,236,196,  3,  1,192,240,252,124, 14,  0,128,224,112,  0,  0,  0,224,248,254,255, 51, 12,  7,  1,  0,128,240,248,254,255, 27, 12,  3,  1,  0,128,240,248,252,252,220,248, 48,  0,  0,128,242,254,255,119, 31, 59,  1,  1,153,124,126,255,239,231,243,253,223,  0, 60,126,255,255,231,227,249,255,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120,120,248,252,127,127,120,120, 56, 56, 56, 28, 28, 12, 15,  7,  0,  0,  3,  3,  3,  3,  1, 15, 15, 15, 12, 12,  6,  3, 31, 63,127,127,112, 48, 24, 12,  6, 15, 31, 63,127,121, 48, 48, 24, 12,  6,  3,  7, 15, 15,  8,  8,  8, 12,  4,  2, 63,127,127,127, 96, 48, 16,  8,  6,  0,  0,  0, 28, 63, 63, 31,  1,  0,  0,  0,  0, 24, 62, 63, 63,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw(logo, sizeof(logo));
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_makai_logo();
        oled_set_cursor(0, 3);
        render_status();
    } else {
        render_logo();
    }
}
#endif
