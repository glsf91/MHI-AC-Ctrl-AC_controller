// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: AC_controller

#include "ui.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
    #define LV_ATTRIBUTE_MEM_ALIGN
#endif

// IMAGE DATA: assets\thermometer24.png
const LV_ATTRIBUTE_MEM_ALIGN uint8_t ui_img_thermometer24_png_data[] = {
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x08,0x00,0x00,0x64,0x00,0x00,0xCC,0x00,0x00,0xC1,0x00,0x00,0x56,0x00,0x00,0x04,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x84,0x00,0x00,0x9B,0x00,0x00,0x1C,0x00,0x00,0x22,0x00,0x00,0xA6,0x00,0x00,0x64,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x07,0x00,0x00,0xDB,0x00,0x00,0x0B,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x14,0x00,0x00,0xC9,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x36,0x00,0x00,0xB9,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xC9,0x00,0x00,0x16,0x00,0x00,0x82,0x00,0x00,0xE8,0x00,0x00,0xE8,0x00,0x00,0x9F,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x38,0x00,0x00,0xB8,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xC8,0x00,0x00,0x18,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x38,
    0x00,0x00,0xB8,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xC8,0x00,0x00,0x18,0x00,0x00,0x0C,0x00,0x00,0xA9,0x00,0x00,0xAE,0x00,0x00,0x19,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x38,0x00,0x00,0xB8,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xC8,0x00,0x00,0x18,0xFF,0xFF,0x00,0x00,0x00,0x31,0x00,0x00,0x35,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x38,0x00,0x00,0xB8,0xFF,0xFF,0x00,0x00,0x00,0x0E,0x00,0x00,0x09,0xFF,0xFF,0x00,0x00,0x00,0xC8,0x00,0x00,0x18,0x00,0x00,0x3F,0x00,0x00,0x70,0x00,0x00,0x70,0x00,0x00,0x4D,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x38,0x00,0x00,0xB8,0xFF,0xFF,0x00,0x00,0x00,0x7C,0x00,0x00,0x65,0xFF,0xFF,0x00,0x00,0x00,0xC8,0x00,0x00,0x18,0x00,0x00,0x3F,0x00,0x00,0x70,0x00,0x00,0x70,0x00,0x00,0x4D,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x38,0x00,0x00,0xB8,0xFF,0xFF,0x00,0x00,0x00,0x80,0x00,0x00,0x68,0xFF,0xFF,0x00,0x00,0x00,0xC8,0x00,0x00,0x18,0xFF,0xFF,0x00,0x00,0x00,0x31,0x00,0x00,0x35,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x38,0x00,0x00,0xB8,0xFF,0xFF,0x00,0x00,0x00,0x80,0x00,0x00,0x68,0xFF,0xFF,0x00,0x00,0x00,0xC8,0x00,0x00,0x18,0x00,0x00,0x0C,
    0x00,0x00,0xA9,0x00,0x00,0xAE,0x00,0x00,0x19,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x38,0x00,0x00,0xB8,0xFF,0xFF,0x00,0x00,0x00,0x80,0x00,0x00,0x68,0xFF,0xFF,0x00,0x00,0x00,0xC8,0x00,0x00,0x18,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x38,0x00,0x00,0xB8,0xFF,0xFF,0x00,0x00,0x00,0x80,0x00,0x00,0x68,0xFF,0xFF,0x00,0x00,0x00,0xC8,0x00,0x00,0x18,0x00,0x00,0x82,0x00,0x00,0xE8,0x00,0x00,0xE8,0x00,0x00,0x9F,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x87,
    0x00,0x00,0xA3,0xFF,0xFF,0x00,0x00,0x00,0x80,0x00,0x00,0x68,0xFF,0xFF,0x00,0x00,0x00,0xB3,0x00,0x00,0x60,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x84,0x00,0x00,0xCE,0x00,0x00,0x12,0xFF,0xFF,0x00,0x00,0x00,0x80,0x00,0x00,0x68,0xFF,0xFF,0x00,0x00,0x00,0x13,0x00,0x00,0xC0,0x00,0x00,0x4C,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x2B,0x00,0x00,0xD5,0x00,0x00,0x12,0x00,0x00,0x05,0x00,0x00,0x76,0x00,0x00,0xE3,0x00,0x00,0xE3,0x00,0x00,0x78,0x00,0x00,0x09,0x00,0x00,0x09,0x00,0x00,0xDC,0x00,0x00,0x19,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x9C,0x00,0x00,0x65,0xFF,0xFF,0x00,0x00,0x00,0x99,0x00,0x00,0x86,0x00,0x00,0x0A,0x00,0x00,0x0E,0x00,0x00,0x99,0x00,0x00,0x82,0xFF,0xFF,0x00,0x00,0x00,0x6F,0x00,0x00,0x5B,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xCA,0x00,0x00,0x17,0xFF,0xFF,0x00,0x00,0x00,0xC9,0x00,0x00,0x08,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x15,0x00,0x00,0xD7,0x00,0x00,0x01,0x00,0x00,0x35,0x00,0x00,0x9D,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xCD,0x00,0x00,0x1C,0x00,0x00,0x06,0x00,0x00,0xE2,0x00,0x00,0x08,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x15,0x00,0x00,0xD2,0x00,0x00,0x01,0x00,0x00,0x27,
    0x00,0x00,0xB5,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xAB,0x00,0x00,0x41,0xFF,0xFF,0x00,0x00,0x00,0x84,0x00,0x00,0x87,0x00,0x00,0x0C,0x00,0x00,0x11,0x00,0x00,0x99,0x00,0x00,0x70,0xFF,0xFF,0x00,0x00,0x00,0x5E,0x00,0x00,0x85,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x4B,0x00,0x00,0xB0,0xFF,0xFF,0x00,0x00,0x00,0x0D,0x00,0x00,0x8D,0x00,0x00,0xDB,0x00,0x00,0xD4,0x00,0x00,0x75,0x00,0x00,0x0A,0x00,0x00,0x01,0x00,0x00,0xBD,0x00,0x00,0x3E,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x03,0x00,0x00,0xB8,0x00,0x00,0x6A,
    0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x03,0x00,0x00,0x02,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x88,0x00,0x00,0x9D,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x06,0x00,0x00,0xAD,0x00,0x00,0xA0,0x00,0x00,0x39,0x00,0x00,0x01,0x00,0x00,0x04,0x00,0x00,0x33,0x00,0x00,0xB0,0x00,0x00,0xAE,0x00,0x00,0x0E,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x03,0x00,0x00,0x5F,0x00,0x00,0xA1,0x00,0x00,0xDA,0x00,0x00,0xE3,0x00,0x00,0xAF,0x00,0x00,0x58,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,
    
};
const lv_img_dsc_t ui_img_thermometer24_png = {
    .header.always_zero = 0,
    .header.w = 24,
    .header.h = 24,
    .data_size = sizeof(ui_img_thermometer24_png_data),
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
    .data = ui_img_thermometer24_png_data
};
