// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: AC_controller

#include "ui.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
    #define LV_ATTRIBUTE_MEM_ALIGN
#endif

// IMAGE DATA: assets\vanesUnknown.png
const LV_ATTRIBUTE_MEM_ALIGN uint8_t ui_img_vanesunknown_png_data[] = {
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x8C,0x00,0x00,0xC5,0x00,0x00,0xBD,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xE1,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xC1,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0x00,0x00,0x01,0x00,0x00,0xBE,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0x00,0x00,0x02,0x00,0x00,0xBD,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0x00,0x00,0x02,0x00,0x00,0xBD,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0x00,0x00,0x02,0x00,0x00,0xBD,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0x00,0x00,0x02,0x00,0x00,0xBD,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0x00,0x00,0x02,0x00,0x00,0xBD,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0x00,0x00,0x02,0x00,0x00,0xBD,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0x00,0x00,0x02,
    0x00,0x00,0xBD,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0x00,0x00,0x02,0x00,0x00,0xBD,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0x00,0x00,0x02,0x00,0x00,0xE9,0x00,0x00,0xAA,0x00,0x00,0xAA,0x00,0x00,0xAA,0x00,0x00,0xAA,0x00,0x00,0xAA,0x00,0x00,0x28,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x11,0x00,0x00,0x11,0x00,0x00,0x11,0x00,0x00,0x11,0x00,0x00,0x11,0x00,0x00,0x5B,0x00,0x00,0x75,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0x00,0x00,0x40,0x00,0x00,0x90,0x00,0x00,0x95,0x00,0x00,0x54,0x00,0x00,0x01,0xFF,0xFF,0x00,0x00,0x00,0x10,0x00,0x00,0xB5,0xFF,0xFF,0x00,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0x5F,0x00,0x00,0xF0,0x00,0x00,0x71,0x00,0x00,0x65,0x00,0x00,0xDE,0x00,0x00,0x93,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xC0,0x00,0x00,0x09,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0xD7,0x00,0x00,0x6E,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x39,0x00,0x00,0xFB,0x00,0x00,0x0B,0xFF,0xFF,0x00,0x00,0x00,0x84,0x00,0x00,0x42,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0x26,0x00,0x00,0x0C,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x3B,0x00,0x00,0xF9,0x00,0x00,0x0B,0xFF,0xFF,0x00,0x00,0x00,0x40,0x00,0x00,0x86,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x1F,0x00,0x00,0xE0,0x00,0x00,0x74,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x06,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x0E,0x00,0x00,0xDF,
    0x00,0x00,0x8B,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xB4,0x00,0x00,0x2E,0x00,0x00,0x22,0x00,0x00,0x22,0x00,0x00,0xC8,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x65,0x00,0x00,0xC8,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x4D,0x00,0x00,0x99,0x00,0x00,0x99,0x00,0x00,0x99,0x00,0x00,0x99,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x59,0x00,0x00,0x6A,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x33,0x00,0x00,0x3E,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x99,0x00,0x00,0xB9,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,
};
const lv_img_dsc_t ui_img_vanesunknown_png = {
    .header.always_zero = 0,
    .header.w = 14,
    .header.h = 23,
    .data_size = sizeof(ui_img_vanesunknown_png_data),
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
    .data = ui_img_vanesunknown_png_data
};
