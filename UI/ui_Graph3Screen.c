// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: AC_controller

#include "ui.h"

void ui_Graph3Screen_screen_init(void)
{
    ui_Graph3Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Graph3Screen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Graph3Screen, lv_color_hex(0x464B55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Graph3Screen, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Graph3Screen, lv_color_hex(0x2D323C), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RootPanel3 = lv_obj_create(ui_Graph3Screen);
    lv_obj_set_width(ui_RootPanel3, lv_pct(100));
    lv_obj_set_height(ui_RootPanel3, lv_pct(100));
    lv_obj_set_align(ui_RootPanel3, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_RootPanel3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_RootPanel3, lv_color_hex(0x239BB4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RootPanel3, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RootPanel3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RootPanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Wifi3 = lv_img_create(ui_RootPanel3);
    lv_img_set_src(ui_Wifi3, &ui_img_icn_wifi_png);
    lv_obj_set_width(ui_Wifi3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Wifi3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Wifi3, -138);
    lv_obj_set_y(ui_Wifi3, -223);
    lv_obj_set_align(ui_Wifi3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Wifi3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Wifi3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_Wifi3, lv_color_hex(0x04F924), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_Wifi3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PagePanel3 = lv_obj_create(ui_RootPanel3);
    lv_obj_set_height(ui_PagePanel3, 50);
    lv_obj_set_width(ui_PagePanel3, lv_pct(100));
    lv_obj_set_align(ui_PagePanel3, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_PagePanel3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PagePanel3, lv_color_hex(0x0F08F7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PagePanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PagePanel3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PagePanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PreviousPage3 = lv_img_create(ui_PagePanel3);
    lv_img_set_src(ui_PreviousPage3, &ui_img_arrow_left_png);
    lv_obj_set_width(ui_PreviousPage3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_PreviousPage3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_PreviousPage3, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_PreviousPage3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_PreviousPage3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_PreviousPage3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_PreviousPage3, 200, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NextPage3 = lv_img_create(ui_PagePanel3);
    lv_img_set_src(ui_NextPage3, &ui_img_arrow_right_png);
    lv_obj_set_width(ui_NextPage3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_NextPage3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_NextPage3, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_NextPage3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_NextPage3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_NextPage3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_NextPage3, 200, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Home3 = lv_img_create(ui_PagePanel3);
    lv_img_set_src(ui_Home3, &ui_img_home_png);
    lv_obj_set_width(ui_Home3, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_Home3, LV_SIZE_CONTENT);    /// 32
    lv_obj_set_align(ui_Home3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Home3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Home3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ChartWatt = lv_chart_create(ui_RootPanel3);
    lv_obj_set_width(ui_ChartWatt, 264);
    lv_obj_set_height(ui_ChartWatt, 338);
    lv_obj_set_x(ui_ChartWatt, 20);
    lv_obj_set_y(ui_ChartWatt, 35);
    lv_obj_set_align(ui_ChartWatt, LV_ALIGN_TOP_MID);
    lv_chart_set_type(ui_ChartWatt, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(ui_ChartWatt, 20);
    lv_chart_set_range(ui_ChartWatt, LV_CHART_AXIS_PRIMARY_Y, 0, 1500);
    lv_chart_set_range(ui_ChartWatt, LV_CHART_AXIS_SECONDARY_Y, 0, 0);
    lv_chart_set_div_line_count(ui_ChartWatt, 16, 6);
    lv_chart_set_axis_tick(ui_ChartWatt, LV_CHART_AXIS_PRIMARY_X, 10, 5, 6, 1, true, 50);
    lv_chart_set_axis_tick(ui_ChartWatt, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 16, 2, true, 50);
    lv_chart_set_axis_tick(ui_ChartWatt, LV_CHART_AXIS_SECONDARY_Y, 0, 5, 0, 2, false, 25);



    lv_obj_set_style_text_color(ui_ChartWatt, lv_color_hex(0xE8E8E8), LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ChartWatt, 255, LV_PART_TICKS | LV_STATE_DEFAULT);

    ui_Label4 = lv_label_create(ui_Graph3Screen);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label4, 7);
    lv_obj_set_y(ui_Label4, -200);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "Power usage Watt");
    lv_obj_set_style_text_color(ui_Label4, lv_color_hex(0xDEDEDE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_PreviousPage3, ui_event_PreviousPage3, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_NextPage3, ui_event_NextPage3, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Home3, ui_event_Home3, LV_EVENT_ALL, NULL);

}
