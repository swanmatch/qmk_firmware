#include "helix.h"

// Each keymap.c should use is_keyboard_master() instead of 'is_master'.
// But keep 'is_master' for a while for backwards compatibility
//  for the old keymap.c.
uint8_t is_master = false;

#ifdef SSD1306OLED
#include "ssd1306.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	return process_record_gfx(keycode,record) && process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    //led_set_user(usb_led);
}
#endif

void matrix_init_kb(void) {
    // Each keymap.c should use is_keyboard_master() instead of is_master.
    // But keep is_master for a while for backwards compatibility
    //  for the old keymap.c.
    is_master = is_keyboard_master();

	matrix_init_user();
};


#ifdef RGB_MATRIX_ENABLE

#ifdef RGB_MATRIX_SPLIT_RIGHT
led_config_t g_led_config = { {
    {  NO_LED,   0,   1,   2,   3,   4,      5 },
    {  NO_LED,  11,  10,   9,   8,   7,      6 },
    {  NO_LED,  12,  13,  14,  15,  16,     17 },
    {      24,  23,  22,  21,  20,  19,     18 },
    {      25,  26,  27,  28,  29,  30,     31 },
    {      37,  36,  35,  34,  33,  32, NO_LED },
    {      38,  39,  40,  41,  42,  43, NO_LED },
    {      49,  48,  47,  46,  45,  44, NO_LED },
    {      50,  51,  52,  53,  54,  55,     56 },
    {      63,  62,  61,  60,  59,  58,     57 },
}, {
    { 139,  16 }, { 174,  13 }, { 208,  20 }, { 208,  38 }, { 174,  48 }, { 139,  52 },
    { 129,  63 }, { 139,  39 }, { 139,  21 }, { 139,   4 }, { 156,   2 }, { 156,  19 },
    { 156,  37 }, { 144,  58 }, { 164,  55 }, { 174,  35 }, { 174,  13 }, { 174,   0 },
    { 191,   3 }, { 191,  20 }, { 191,  37 }, { 208,  42 }, { 208,  24 }, { 208,   7 }, { 224,   7 },
    { 224,  24 }, { 224,  41 }, {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 },
    {  85,  52 }, {  95,  63 }, {  85,  39 }, {  85,  21 }, {  85,   4 }, {  68,   2 },
    {  68,  19 }, {  68,  37 }, {  80,  58 }, {  60,  55 }, {  50,  35 }, {  50,  13 },
    {  50,   0 }, {  33,   3 }, {  33,  20 }, {  33,  37 }, {  16,  42 }, {  16,  24 },
    {  16,   7 }, {   0,   7 }, {   0,  24 }, {   0,  41 }, {  16,   7 }, {   0,   7 }, {   0,  24 },
    {  16,   7 }, {   0,   7 }, {   0,  24 }, {   0,  41 }, {  16,   7 }, {   0,   7 }, {   0,  24 }
}, {
    4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1,
       4, 4, 4, 4, 4, 1,
       4, 4, 4, 4, 4, 1,
       4, 4, 4, 4, 4, 1,
    4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1,
} };
#else
led_config_t g_led_config = { {
    {       5,   4,   3,   2,   1,   0, NO_LED },
    {       6,   7,   8,   9,  10,  11, NO_LED },
    {      17,  16,  15,  14,  13,  12, NO_LED },
    {      18,  19,  20,  21,  22,  23,     24 },
    {      31,  30,  29,  28,  27,  26,     25 },
    {  NO_LED,  32,  33,  34,  35,  36,     37 },
    {  NO_LED,  43,  42,  41,  40,  39,     38 },
    {  NO_LED,  44,  45,  46,  47,  48,     49 },
    {      56,  55,  54,  53,  52,  51,     50 },
    {      57,  58,  59,  60,  61,  62,     63 },
}, {
    {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 },
    {  85,  39 }, {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }, {  68,  37 },
    {  60,  55 }, {  50,  35 }, {  50,  13 }, {  50,   0 }, {  33,   3 }, {  33,  20 },
    {  16,  42 }, {  16,  24 }, {  16,   7 }, {   0,   7 }, {   0,  24 }, {   0,  41 },
    { 174,  13 }, { 208,  20 }, { 208,  38 }, { 174,  48 }, { 139,  52 }, { 129,  63 },
    { 139,  21 }, { 139,   4 }, { 156,   2 }, { 156,  19 }, { 156,  37 }, { 144,  58 }, { 164,  55 },
    { 174,  35 }, { 174,  13 }, { 174,   0 }, { 191,   3 }, { 191,  20 }, { 191,  37 }, { 208,  42 }
}, {
    4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1,
       4, 4, 4, 4, 4, 1,
       4, 4, 4, 4, 4, 1,
       4, 4, 4, 4, 4, 1,
    4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1,
} };
#endif
#endif
void keyboard_post_init_kb(void) {
#if defined(DEBUG_MATRIX_SCAN_RATE)
    debug_enable = true;
#endif
    keyboard_post_init_user();
}

#if defined(SPLIT_KEYBOARD) && defined(SSD1306OLED)
void matrix_slave_scan_user(void) {
    matrix_scan_user();
}
#endif
