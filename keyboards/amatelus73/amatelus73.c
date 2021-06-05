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

#include "amatelus73.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

/*
void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware

    return process_record_user(keycode, record);
}

bool led_update_kb(led_t led_state) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    return led_update_user(led_state);
}
*/

#define LED_LAYOUT(\
    L1,  L2,  L3,  L4,  L5,  L6,  L7,  L8,       L9,  L10, L11, L12, L13, L14, L15, L16,\
    L17, L18, L19, L20, L21, L22, L23, L24,      L25, L26, L27, L28, L29, L30, L31, L32,\
         L33, L34, L35, L36, L37, L38, L39, L40, L41, L42, L43, L44, L45, L46, L47,     \
    L48, L49, L50, L51, L52, L53, L54, L55,      L56, L57, L58, L59, L60, L61, L62, L63,\
    L64, L65,                L66, L67, L68,      L69, L70, L71,           L72, L73, L74 \
) { \
    L16, L15, L14, L13, L12, L11, L10, L9,       L8,  L7,  L6,  L5,  L4,  L3,  L2,  L1, \
    L17, L18, L19, L20, L21, L22, L23, L24,      L25, L26, L27, L28, L29, L30, L31, L32,\
         L33, L34, L35, L36, L37, L38, L39, L40, L41, L42, L43, L44, L45, L46, L47,     \
    L63, L62, L61, L60, L59, L58, L57, L56,      L55, L54, L53, L52, L51, L50, L49, L48,\
    L64, L65,                L66, L67, L68,      L69, L70, L71,           L72, L73, L74 \
}

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  {14,    17,    46,    48,    72    },
  {12,    19,    44,    50,    NO_LED},
  {10,    21,    42,    52,    70    },
  { 8,    23,    10,    54,    NO_LED},
  { 6,    25,    37,    56,    67    },
  { 4,    27,    35,    58,    NO_LED},
  { 2,    29,    33,    60,    65    },
  { 0,    31,    NO_LED,62,    63    },
  {15,    16,    NO_LED,47,    73    },
  {13,    18,    45,    49,    NO_LED},
  {11,    20,    43,    51,    71    },
  { 9,    22,    41,    53,    69    },
  { 7,    24,    38,    55,    68    },
  { 5,    26,    36,    57,    66    },
  { 3,    28,    34,    59,    NO_LED},
  { 1,    30,    32,    61,    64    },
},{
  {210,64},{196,64},{183,64},{169,64},{155,64},{141,64},{128,64},{114,64},         {100,64},{ 86,64},{ 72,64},{ 59,64},{ 45,64},{ 31,64},{ 17,64},{  3,64},
  {  3,48},{ 17,48},{ 38,48},{ 52,48},{ 65,48},{ 79,48},{ 93,48},{107,48},         {121,48},{134,48},{148,48},{162,48},{176,48},{190,48},{203,48},{224,48},
           {207,32},{193,32},{179,32},{165,32},{152,32},{138,32},{124,32},{114,32},{103,32},{ 90,32},{ 76,32},{ 62,32},{ 48,32},{ 34,32},{ 10,32},
  {  0,16},{ 31,16},{ 45,16},{ 59,16},{ 72,16},{ 86,16},{100,16},{114,16},{128,16},{141,16},{155,16},{169,16},{183,16},{196,16},{210,16},{224,16},
  {224, 0},{210, 0},{196, 0},                  {152, 0},{134, 0},{121, 0},         {107, 0},{ 90, 0},{ 76, 0},                           { 14, 0},{  0, 0},
}, LED_LAYOUT(
  1,  1, 4, 4, 4, 4, 4, 1, 1, 1, 4, 4, 4, 4, 4, 1,
  1, 1, 4, 4, 4, 4, 4, 1,      1, 4, 4, 4, 4, 4, 1, 1,
    1, 4, 4, 4, 4, 4, 1,   8,   1, 4, 4, 4, 4, 4, 1,
1, 1, 4, 4, 4, 4, 4, 1,    1,    1, 4, 4, 4, 4, 4, 1,
   1, 1,          1, 1, 1,    1, 1, 1,          1, 1, 1
) };

#endif
