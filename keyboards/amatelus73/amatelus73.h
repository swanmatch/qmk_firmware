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

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    k101,  k102,  k103,  k104,  k105,  k106,  k107,  k108,  k109,  k110,  k111,  k112,  k113,  k114,  k115,  k116,\
    k201,  k202,  k203,  k204,  k205,  k206,  k207,  k208,  k209,  k210,  k211,  k212,  k213,  k214,  k215,  k216,\
           k302,  k303,  k304,  k305,  k306,  k307,  k308,  k309,  k310,  k311,  k312,  k313,  k314,  k315,       \
    k401,  k402,  k403,  k404,  k405,  k406,  k407,  k408,  k409,  k410,  k411,  k412,  k413,  k414,  k415,  k416,\
    k501,  k502,                k505,  k506,  k507,         k509,  k510,  k511,                k514,  k515,  k516 \
) \
{ \
    { k102,  k202,  k302,  k402,  k502 },\
    { k104,  k204,  k304,  k404,  KC_NO},\
    { k106,  k206,  k306,  k406,  k506 },\
    { k108,  k208,  k308,  k408,  KC_NO},\
    { k110,  k210,  k310,  k410,  k510 },\
    { k112,  k212,  k312,  k412,  KC_NO},\
    { k114,  k214,  k314,  k414,  k514 },\
    { k116,  k216,  KC_NO, k416,  k516 },\
    { k101,  k201,  KC_NO, k401,  k501 },\
    { k103,  k203,  k303,  k403,  KC_NO},\
    { k105,  k205,  k305,  k405,  k505 },\
    { k107,  k207,  k307,  k407,  k507 },\
    { k109,  k209,  k309,  k409,  k509 },\
    { k111,  k211,  k311,  k411,  k511 },\
    { k113,  k213,  k313,  k413,  KC_NO},\
    { k115,  k215,  k315,  k415,  k515 },\
}
