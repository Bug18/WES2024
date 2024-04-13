// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_MainScreen_screen_init(void)
{
    ui_MainScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_MainScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_MainScreen, &ui_img_test_venus_320x240_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_MainScreen, 180, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WelcomeText = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_WelcomeText, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WelcomeText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WelcomeText, 7);
    lv_obj_set_y(ui_WelcomeText, -59);
    lv_obj_set_align(ui_WelcomeText, LV_ALIGN_CENTER);
    lv_label_set_text(ui_WelcomeText, "Welcome to");
    lv_obj_set_style_text_color(ui_WelcomeText, lv_color_hex(0xF1EE72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WelcomeText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_WelcomeText, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_WelcomeText, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_InfoButton = lv_btn_create(ui_MainScreen);
    lv_obj_set_width(ui_InfoButton, 100);
    lv_obj_set_height(ui_InfoButton, 50);
    lv_obj_set_x(ui_InfoButton, -66);
    lv_obj_set_y(ui_InfoButton, 38);
    lv_obj_set_align(ui_InfoButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_InfoButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_InfoButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_InfoButton, lv_color_hex(0xFFF5F5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_InfoButton, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_InfoButton, lv_color_hex(0x3E4247), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_InfoButton, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_InfoButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_InfoButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_InfoButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_InfoButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_InfoButton, lv_color_hex(0x0A0A0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_InfoButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StartGameButton = lv_btn_create(ui_MainScreen);
    lv_obj_set_width(ui_StartGameButton, 100);
    lv_obj_set_height(ui_StartGameButton, 50);
    lv_obj_set_x(ui_StartGameButton, 82);
    lv_obj_set_y(ui_StartGameButton, 38);
    lv_obj_set_align(ui_StartGameButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_StartGameButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_StartGameButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_StartGameButton, lv_color_hex(0xFFF5F5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StartGameButton, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_StartGameButton, lv_color_hex(0x3E4247), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_StartGameButton, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_StartGameButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_StartGameButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_StartGameButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_StartGameButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_InfoText = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_InfoText, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_InfoText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_InfoText, -67);
    lv_obj_set_y(ui_InfoText, 36);
    lv_obj_set_align(ui_InfoText, LV_ALIGN_CENTER);
    lv_label_set_text(ui_InfoText, "Info");
    lv_obj_set_style_text_color(ui_InfoText, lv_color_hex(0x191919), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_InfoText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_InfoText, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StartGameText = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_StartGameText, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_StartGameText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_StartGameText, 82);
    lv_obj_set_y(ui_StartGameText, 37);
    lv_obj_set_align(ui_StartGameText, LV_ALIGN_CENTER);
    lv_label_set_text(ui_StartGameText, "Start game");
    lv_obj_set_style_text_color(ui_StartGameText, lv_color_hex(0x0F0F0F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartGameText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartGameText, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BitTraveller = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_BitTraveller, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BitTraveller, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_BitTraveller, 8);
    lv_obj_set_y(ui_BitTraveller, -31);
    lv_obj_set_align(ui_BitTraveller, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BitTraveller, "BitTraveller");
    lv_obj_set_style_text_font(ui_BitTraveller, &lv_font_montserrat_38, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Date = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_Date, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Date, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Date, -104);
    lv_obj_set_y(ui_Date, -103);
    lv_obj_set_align(ui_Date, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Date, "DD:MM:YYYY");
    lv_obj_set_style_text_font(ui_Date, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Hour = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_Hour, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Hour, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Hour, 111);
    lv_obj_set_y(ui_Hour, -101);
    lv_obj_set_align(ui_Hour, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Hour, "HH:MM:SS");
    lv_obj_set_style_text_font(ui_Hour, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_InfoButton, ui_event_InfoButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_StartGameButton, ui_event_StartGameButton, LV_EVENT_ALL, NULL);

}