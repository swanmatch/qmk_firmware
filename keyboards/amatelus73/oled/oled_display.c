#include QMK_KEYBOARD_H
#ifdef OLED_DRIVER_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

extern rgb_config_t rgb_matrix_config;
rgb_config_t rgb_matrix_config_bak;

void render_led_stat(void) {
//   oled_write("  LEDMode: ", false);
//   static char led_modes[20][12] = {
//     "Static",
//     "Breath1", "Breath2", "Breath3", "Breath4",
//     "Mood1",   "Mood2",   "Mood3",
//     "Swirl1",  "Swirl2",  "Swirl3",  "Swirl4", "Swirl5", "Swirl6",
//     "Snake1",  "Snake2",  "Snake3",  "Snake4", "Snake5", "Snake6"
//  };
//   oled_write(led_modes[rgblight_config.mode-1], false);|||||
//   oled_write("\n", false);
  static char led_buf[24] = "LED state ready.\n";
  if (rgb_matrix_config_bak.enable != rgb_matrix_config.enable ||
      rgb_matrix_config_bak.mode != rgb_matrix_config.mode ||
      rgb_matrix_config_bak.hsv.h != rgb_matrix_config.hsv.h ||
      rgb_matrix_config_bak.hsv.s != rgb_matrix_config.hsv.s ||
      rgb_matrix_config_bak.hsv.v != rgb_matrix_config.hsv.v
  ) {
    snprintf(led_buf, sizeof(led_buf) - 1, "   H:%3d S:%3d V:%3d\n",
      rgb_matrix_config.hsv.h,
      rgb_matrix_config.hsv.s,
      rgb_matrix_config.hsv.v);
    rgb_matrix_config_bak = rgb_matrix_config;
  }
  oled_write(led_buf, false);
}

void render_layer_stat(void) {
  static char layer_names[6][6] = {
    "Base",
    "Raise",
    "Lower",
    "Adjust"
  };
  layer_state_t layer = get_highest_layer(layer_state);
  oled_write("   Layer: ", false);
  oled_write(layer_names[layer], false);
  oled_write("\n", false);
}

static void render_mod_stat(void) {
    uint8_t modifiers = get_mods();
    // led_t led_state = host_keyboard_led_state();
    // oled_write("Caps", led_state.caps_lock);
    // oled_write(" ", false);
    // oled_write("Num", led_state.num_lock);
    // oled_write(" ", false);
    oled_write("   ", false);
    oled_write("Ctrl", (modifiers & MOD_MASK_CTRL));
    oled_write(" ", false);
    oled_write("Shift", (modifiers & MOD_MASK_SHIFT));
    oled_write(" ", false);
    oled_write("Alt", (modifiers & MOD_MASK_ALT));
    oled_write(" ", false);
    oled_write("OS", (modifiers & MOD_MASK_GUI));
}
void oled_task_user(void) {
    // LOGO
    // static const char PROGMEM qmk_logo[] = {
    //     0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    //     0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    //     0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    // };
    // oled_write_P(qmk_logo, false);
    oled_write("Amatelus73\n", false);
    render_led_stat();
    render_layer_stat();
    render_mod_stat();
}
#endif
