// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_StartGameScreen_screen_init(void)
{
    ui_StartGameScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_StartGameScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_StartGameScreen, &ui_img_test_venus_320x240_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_StartGameScreen, 130, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Date3 = lv_label_create(ui_StartGameScreen);
    lv_obj_set_width(ui_Date3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Date3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Date3, -104);
    lv_obj_set_y(ui_Date3, -103);
    lv_obj_set_align(ui_Date3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Date3, "DD:MM:YYYY");
    lv_obj_set_style_text_font(ui_Date3, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Hour3 = lv_label_create(ui_StartGameScreen);
    lv_obj_set_width(ui_Hour3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Hour3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Hour3, 111);
    lv_obj_set_y(ui_Hour3, -101);
    lv_obj_set_align(ui_Hour3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Hour3, "HH:MM:SS");
    lv_obj_set_style_text_font(ui_Hour3, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TicTackToeLabel = lv_label_create(ui_StartGameScreen);
    lv_obj_set_width(ui_TicTackToeLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TicTackToeLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TicTackToeLabel, 5);
    lv_obj_set_y(ui_TicTackToeLabel, -43);
    lv_obj_set_align(ui_TicTackToeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TicTackToeLabel, "TIC - TACK - TOE");
    lv_obj_set_style_text_font(ui_TicTackToeLabel, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_selectSignLabel = lv_label_create(ui_StartGameScreen);
    lv_obj_set_width(ui_selectSignLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_selectSignLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_selectSignLabel, -2);
    lv_obj_set_y(ui_selectSignLabel, -10);
    lv_obj_set_align(ui_selectSignLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_selectSignLabel, "- select your sign -");

    ui_XButton = lv_btn_create(ui_StartGameScreen);
    lv_obj_set_width(ui_XButton, 100);
    lv_obj_set_height(ui_XButton, 50);
    lv_obj_set_x(ui_XButton, -66);
    lv_obj_set_y(ui_XButton, 38);
    lv_obj_set_align(ui_XButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_XButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_XButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_XButton, lv_color_hex(0xFFF5F5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_XButton, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_XButton, lv_color_hex(0x3E4247), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_XButton, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_XButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_XButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_XButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_XButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_XButton, lv_color_hex(0x0A0A0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_XButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_OButton = lv_btn_create(ui_StartGameScreen);
    lv_obj_set_width(ui_OButton, 100);
    lv_obj_set_height(ui_OButton, 50);
    lv_obj_set_x(ui_OButton, 82);
    lv_obj_set_y(ui_OButton, 38);
    lv_obj_set_align(ui_OButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_OButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_OButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_OButton, lv_color_hex(0xFFF5F5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_OButton, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_OButton, lv_color_hex(0x3E4247), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_OButton, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_OButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_OButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_OButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_OButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_XLabel = lv_label_create(ui_StartGameScreen);
    lv_obj_set_width(ui_XLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_XLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_XLabel, -69);
    lv_obj_set_y(ui_XLabel, 38);
    lv_obj_set_align(ui_XLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_XLabel, "X");
    lv_obj_set_style_text_color(ui_XLabel, lv_color_hex(0x060606), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_XLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_XLabel, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_OLabel = lv_label_create(ui_StartGameScreen);
    lv_obj_set_width(ui_OLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_OLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_OLabel, 83);
    lv_obj_set_y(ui_OLabel, 38);
    lv_obj_set_align(ui_OLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_OLabel, "O");
    lv_obj_set_style_text_color(ui_OLabel, lv_color_hex(0x050505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_OLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_OLabel, &lv_font_montserrat_44, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BackHomeButton2 = lv_btn_create(ui_StartGameScreen);
    lv_obj_set_width(ui_BackHomeButton2, 117);
    lv_obj_set_height(ui_BackHomeButton2, 24);
    lv_obj_set_x(ui_BackHomeButton2, -94);
    lv_obj_set_y(ui_BackHomeButton2, 105);
    lv_obj_set_align(ui_BackHomeButton2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BackHomeButton2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BackHomeButton2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BackHomeButton2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BackHomeButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BackHome2 = lv_label_create(ui_StartGameScreen);
    lv_obj_set_width(ui_BackHome2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BackHome2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_BackHome2, -94);
    lv_obj_set_y(ui_BackHome2, 104);
    lv_obj_set_align(ui_BackHome2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BackHome2, "Back to Home");
    lv_obj_set_style_text_color(ui_BackHome2, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BackHome2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_XButton, ui_event_XButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_OButton, ui_event_OButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BackHomeButton2, ui_event_BackHomeButton2, LV_EVENT_ALL, NULL);

}
