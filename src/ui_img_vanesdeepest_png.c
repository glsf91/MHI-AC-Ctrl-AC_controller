// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: AC_controller

#include "ui.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
    #define LV_ATTRIBUTE_MEM_ALIGN
#endif

// IMAGE DATA: assets\vanesDeepest.png
const LV_ATTRIBUTE_MEM_ALIGN uint8_t ui_img_vanesdeepest_png_data[] = {
    0x00,0x00,0x8A,0x00,0x00,0xC8,0x00,0x00,0xC0,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xE1,0x00,0x00,0xC1,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0xE5,0x00,0x00,0x99,0x00,0x00,0x99,0x00,0x00,0x99,0x00,0x00,0x99,0x00,0x00,0x99,0x00,0x00,0x23,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x72,0x00,0x00,0x71,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x13,0x00,0x00,0xB2,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xC3,0x00,0x00,0x06,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x1A,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x8A,0x00,0x00,0x3D,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x7B,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x46,0x00,0x00,0x80,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x08,0x00,0x00,0xD8,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x08,0x00,0x00,0xBC,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x57,0x00,0x00,0xEF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xB9,0x00,0x00,0x0E,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xBF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xB7,0x00,0x00,0xF4,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x5F,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0x00,0x00,0xBB,0xFF,0xFF,0x00,0x00,0x00,0x1A,0x00,0x00,0xFC,0x00,0x00,0xFA,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x78,0x00,0x00,0xFF,0x00,0x00,0xFF,
    0x00,0x00,0x01,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x6D,0x00,0x00,0xBA,0x00,0x00,0xE7,0x00,0x00,0x06,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
};
const lv_img_dsc_t ui_img_vanesdeepest_png = {
    .header.always_zero = 0,
    .header.w = 12,
    .header.h = 23,
    .data_size = sizeof(ui_img_vanesdeepest_png_data),
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
    .data = ui_img_vanesdeepest_png_data
};

