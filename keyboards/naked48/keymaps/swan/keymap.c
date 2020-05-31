#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
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

#define ALTF5  LALT_T(KC_F5)
#define SPACE  LSFT_T(KC_SPC)
#define CALC   LT(_CALC, KC_ESC)
#define ENTER  LCTL_T(KC_ENT)
#define CUSL   LT(_CURSOL, KC_TAB)
#define WINF12 GUI_T(KC_F12)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T,               KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_EQL,
    KC_LSFT,  KC_A, KC_S, KC_D, KC_F, KC_G,               KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LCTRL, KC_Z, KC_X, KC_C, KC_V, KC_B,               KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
    KC_LGUI, KC_PSCR, ALTF5, KC_BSPC, SPACE, CALC,  CUSL, ENTER, KC_DEL, WINF12, KC_PSCR, KC_MENU
  ),

  [_CURSOL] = LAYOUT(
    RESET,   KC_F1,   KC_F2,      KC_PGUP, KC_F4,      KC_F5,                           KC_F6,   KC_F7,        KC_UP,   KC_F9,        KC_F10,  RESET,
    _______, KC_TILD, KC_HOME,    KC_PGDN, KC_END,     KC_LPRN,                         KC_RPRN, KC_LEFT,      KC_DOWN, KC_RGHT,      KC_PIPE, KC_F11,
    _______, KC_GRV,  C(KC_LEFT), KC_F3,   C(KC_RGHT), S(ALTAB),                        ALTAB,   LCA(KC_LEFT), KC_F8,   LCA(KC_RGHT), KC_BSLS, RGBRST,
                    _______, _______, _______, _______, C(KC_SPC), MO(_ADJUST), _______, _______, _______, _______, _______, _______
  ),

  [_CALC] = LAYOUT(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7, KC_8, KC_9, KC_0,    _______,
    _______, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LBRC,                        KC_RBRC, KC_4, KC_5, KC_6, KC_PPLS, _______,
    _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_EXLM, KC_LCBR,                        KC_RCBR, KC_1, KC_2, KC_3, KC_PEQL, _______,
             _______, _______, _______, _______, _______, _______,  MO(_ADJUST), KC_0, KC_00, KC_PDOT, _______, _______
  ),

  [_ADJUST] = LAYOUT(
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    RGB_SPI, RGB_MOD,  RGB_VAI, RGB_SAI, RGB_HUI, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    RGB_SPD, RGB_RMOD, RGB_VAD, RGB_SAD, RGB_HUD, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
};

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
