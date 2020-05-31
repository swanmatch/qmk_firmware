/* Copyright 2018 Salicylic_acid3
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

#pragma once

/* Select hand configuration */

//#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

//#define USE_SERIAL

#define TAPPING_TERM 200
#define RGBLIGHT_EFFECT_SNAKE_LENGTH RGBLED_NUM

#undef RGBLIGHT_LIMIT_VAL
#undef RGBLIGHT_VAL_STEP
#undef RGBLIGHT_HUE_STEP
#undef RGBLIGHT_SAT_STEP
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 5
#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
