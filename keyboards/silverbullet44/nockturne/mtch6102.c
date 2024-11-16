/* Copyright 2020 sekigon-gonnoc
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
#include "report.h"
#include "mtch6102.h"
#include "i2c_master.h"
#include <stdint.h>
#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif

#ifndef I2C_TIMEOUT
#    define I2C_TIMEOUT 500
#endif

#ifndef I2C_7BIT_ADDR
#    define I2C_7BIT_ADDR(addr) (addr << 1)
#endif

typedef union {
    struct {
        uint8_t status, x_msb, y_msb, xy_lsb, gesture;
    };
    uint8_t dat[5];
} mtch6102_reg_t;

uint16_t check_mtch6102() {
    uint8_t dat[2] = {0};

    if (i2c_readReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), 0, dat, sizeof(dat), I2C_TIMEOUT)) {
        return 0;
    }

    return ((uint16_t)dat[0] << 8) | dat[1];
}

void pointing_device_driver_init(void) {
    uint8_t dat = 0b0011;
    uint8_t res = 0;

    i2c_init();
    res |= i2c_writeReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_MODE, &dat, 1, I2C_TIMEOUT);

    uint8_t default_config[] = {
        0x09, 0x06, 0x06, 0x37, 0x28, 0x85, 0x02, 0x4C, 0x06, 0x10, 0x04, 0x01, 0x01, 0x0A, 0x00, 0x14, 0x14, 0x02, 0x01, 0x01, 0x05, 0x00, 0x00, 0x40, 0x40, 0x19, 0x19, 0x40, 0x32, 0x00, 0x0C, 0x20, 0x04, 0x2D, 0x2D, 0x25,

    };
    res |= i2c_writeReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_CFG_START, default_config, sizeof(default_config), I2C_TIMEOUT);

    dat = 0x20;
    res |= i2c_writeReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_CMD, &dat, 1, I2C_TIMEOUT);

    // set HOLD time
    dat = 0x10;
    res |= i2c_writeReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_HOLD_TIME, &dat, 1, I2C_TIMEOUT);
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    mtch6102_data_t mtch6102_data = {0};
    bool is_valid = read_mtch6102(&mtch6102_data);

    if (is_valid) {
        mouse_report = process_mtch6102(mtch6102_data, mouse_report);
    }

    return mouse_report;
}


// report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
//     // right_report.h = left_report.x;
//     // right_report.v = left_report.y;
//     // left_report.x = 0;
//     // left_report.y = 0;
//     // if (left_report.y > 0 && right_report.y > 0) {
//     //     // SWIPE UP
//     //     right_report.v = 1;
//     //     left_report.v = 1;
//     //     right_report.y = 0;
//     //     left_report.y = 0;
//     // } else if (left_report.y < 0 && right_report.y < 0 ) {
//     //     // SWIPE DOWN
//     //     right_report.v = -1;
//     //     left_report.v = -1;
//     //     right_report.y = 0;
//     //     left_report.y = 0;
//     // }
//     // if ( left_report.x > 0 && right_report.x > 0) {
//     //     // SWIPE RIGHT
//     //     right_report.h = 1;
//     //     left_report.h = 1;
//     //     right_report.x = 0;
//     //     left_report.x = 0;
//     // } else if ( left_report.x < 0 && right_report.x < 0) {
//     //     // SWIPE RIGHT
//     //     right_report.h = -1;
//     //     left_report.h = -1;
//     //     right_report.x = 0;
//     //     left_report.x = 0;
//     // } else if ( left_report.x > 0 && right_report.x < 0) {
//     //     // PINCH IN
//     //     tap_code16(LCTL(KC_MINS));
//     //     right_report.x = 0;
//     //     left_report.x = 0;
//     // } else if ( left_report.x < 0 && right_report.x > 0) {
//     //     // PINCH OUT
//     //     tap_code16(LCTL(KC_EQL));
//     //     right_report.x = 0;
//     //     left_report.x = 0;
//     // }
//     // uprintf("pointing_device_task_combined_user\n");
//     // if (left_report.x == 0 || left_report.y == 0) {
//     //     if (right_report.x != 0 && right_report.y != 0) {
//     //         uprintf("right: x: %d, y: %d\n", right_report.x, right_report.y);
//     //     }
//     //     return right_report;
//     // }
//     if (right_report.x != 0 || right_report.y != 0 || left_report.x != 0 || left_report.y != 0) {
//         uprintf("left: x: %d, y: %d, h: %d, v: %d | right: x: %d, y: %d, h: %d, v: %d \n ", left_report.x, left_report.y, left_report.h, left_report.v, right_report.x, right_report.y, right_report.h, right_report.v);
//     }
//     // left_report.x = 0;
//     left_report.y = 0;
//     left_report.h = 0;
//     left_report.v = 0;

//     // uprintf("\n", right_report.x, right_report.y);
//     // return pointing_device_combine_reports(right_report, left_report);
// }

bool read_mtch6102(mtch6102_data_t* const data) {
    mtch6102_reg_t reg;

    if (i2c_readReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_STAT, reg.dat, sizeof(mtch6102_reg_t), I2C_TIMEOUT)) {
        uprintf("regread error\n");
        return false;
    }

    data->gesture = reg.gesture;
    data->status  = reg.status;
    data->x       = (reg.x_msb << 4) | (reg.xy_lsb >> 4);
    data->y       = (reg.y_msb << 4) | (reg.xy_lsb & 0xF);

    return true;
}

report_mouse_t process_mtch6102(mtch6102_data_t data, report_mouse_t rep_mouse) {
    static bool release_button = false;
    static uint16_t buf_x = 0;
    static uint16_t buf_y = 0;

    if (data.status & TOUCH) {
        // if (is_keyboard_master()) {
            rep_mouse.x = (mouse_xy_report_t) (data.y - buf_y);
            rep_mouse.y = (mouse_xy_report_t) (data.x - buf_x);
        // } else {
        //     int16_t diff_y = data.y - buf_y;
        //     int16_t diff_x = data.x - buf_x;
        //     if (diff_y < INT8_MIN || diff_y > INT8_MAX) {
        //         diff_y = (diff_y < INT8_MIN) ? INT8_MIN : INT8_MAX;
        //     }
        //     if (diff_x < INT8_MIN || diff_x > INT8_MAX) {
        //         diff_x = (diff_x < INT8_MIN) ? INT8_MIN : INT8_MAX;
        //     }
        //     // uint16_t data_x = data.x;
        //     // uint16_t data_y = data.y;
        //     rep_mouse.x = diff_y;
        //     rep_mouse.y = diff_x;
        //     // rep_mouse.y = diff_x;
        //     // rep_mouse.x = diff_y;
        //     // rep_mouse.x = data.y / 4;
        //     // rep_mouse.y = data.x / 4;
        //     // rep_mouse.h = buf_y / 4;
        //     // rep_mouse.v = buf_x / 4;
            // rep_mouse.x = data.y;
            // rep_mouse.y = data.x;
            // rep_mouse.h = buf_y;
            // rep_mouse.v = buf_x;
        // }
    } else {
        rep_mouse.x = 0;
        rep_mouse.y = 0;
    }
    buf_x = data.x;
    buf_y = data.y;

    if ((data.status & GESTURE) && (data.gesture == GES_TAP)) {
        rep_mouse.buttons = 1;
        release_button = true;
    // } else if ((data.status & GESTURE) && ( data.gesture == GES_DOUBLE_TAP)) {
    //     rep_mouse.buttons = 2;
    //     release_button = true;
    } else if ((data.status & GESTURE) && ( data.gesture == GES_HOLD)) {
        rep_mouse.buttons = 2;
        release_button = true;
    } else if (release_button) {
        rep_mouse.buttons = 0;
    }

    return rep_mouse;
}

int sleep_mtch6102(void) {
    uint8_t dat = 0b0000;
    return i2c_writeReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_MODE, &dat, 1, I2C_TIMEOUT);
}

void test_mtch6102(void) {
    uint8_t dat = 0x08;

    // start manufacturing test
    uint8_t res = i2c_writeReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_CMD, &dat, 1, I2C_TIMEOUT);

    if (res != 0) {
        xprintf("test command failed\n");
        return;
    }

    uint32_t retry = 100;
    do {
        i2c_readReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_CMD, &dat, 1, I2C_TIMEOUT);

        if ((dat & 0x08) == 0) {
            // manufacturing test end
            break;
        }
    } while (retry--);

    if (retry == 0) {
        xprintf("test timeout\n");
        return;
    }

    uint8_t mfg_test_res[6] = {0};
    i2c_readReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), 0xD0, mfg_test_res, sizeof(mfg_test_res), I2C_TIMEOUT);

    xprintf("res:0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n", mfg_test_res[0], mfg_test_res[1], mfg_test_res[2], mfg_test_res[3], mfg_test_res[4], mfg_test_res[5]);
}
