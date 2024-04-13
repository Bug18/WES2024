// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_EndGameScreen_screen_init(void)
{
    ui_EndGameScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_EndGameScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_EndGameScreen, &ui_img_test_venus_320x240_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_EndGameScreen, 130, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Date1 = lv_label_create(ui_EndGameScreen);
    lv_obj_set_width(ui_Date1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Date1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Date1, -104);
    lv_obj_set_y(ui_Date1, -103);
    lv_obj_set_align(ui_Date1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Date1, "DD:MM:YYYY");
    lv_obj_set_style_text_font(ui_Date1, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Hour1 = lv_label_create(ui_EndGameScreen);
    lv_obj_set_width(ui_Hour1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Hour1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Hour1, 111);
    lv_obj_set_y(ui_Hour1, -101);
    lv_obj_set_align(ui_Hour1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Hour1, "HH:MM:SS");
    lv_obj_set_style_text_font(ui_Hour1, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_GameOverLabel = lv_label_create(ui_EndGameScreen);
    lv_obj_set_width(ui_GameOverLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_GameOverLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_GameOverLabel, 7);
    lv_obj_set_y(ui_GameOverLabel, -17);
    lv_obj_set_align(ui_GameOverLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_GameOverLabel, "Game over");
    lv_obj_set_style_text_color(ui_GameOverLabel, lv_color_hex(0xF1EE72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_GameOverLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_GameOverLabel, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WinLabel = lv_label_create(ui_EndGameScreen);
    lv_obj_set_width(ui_WinLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WinLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WinLabel, 10);
    lv_obj_set_y(ui_WinLabel, 24);
    lv_obj_set_align(ui_WinLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_WinLabel, "You won! Well done :)");
    lv_obj_add_flag(ui_WinLabel, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_set_style_text_font(ui_WinLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LoseLabel = lv_label_create(ui_EndGameScreen);
    lv_obj_set_width(ui_LoseLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LoseLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LoseLabel, 10);
    lv_obj_set_y(ui_LoseLabel, 24);
    lv_obj_set_align(ui_LoseLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LoseLabel, "             You lost! \nBetter luck next time :/");
    lv_obj_set_style_text_font(ui_LoseLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BackHomeButton = lv_btn_create(ui_EndGameScreen);
    lv_obj_set_width(ui_BackHomeButton, 109);
    lv_obj_set_height(ui_BackHomeButton, 21);
    lv_obj_set_x(ui_BackHomeButton, -94);
    lv_obj_set_y(ui_BackHomeButton, 105);
    lv_obj_set_align(ui_BackHomeButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BackHomeButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BackHomeButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BackHomeButton, lv_color_hex(0xF1EE72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BackHomeButton, 150, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BackHome = lv_label_create(ui_EndGameScreen);
    lv_obj_set_width(ui_BackHome, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BackHome, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_BackHome, -93);
    lv_obj_set_y(ui_BackHome, 106);
    lv_obj_set_align(ui_BackHome, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BackHome, "Back to Home");
    lv_obj_set_style_text_color(ui_BackHome, lv_color_hex(0x28375F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BackHome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_BackHomeButton, ui_event_BackHomeButton, LV_EVENT_ALL, NULL);

}