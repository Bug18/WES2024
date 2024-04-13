/**
 * @file gui_app.c
 *
 * @brief This file runs the UI.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "gui_app.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

/* Littlevgl specific */
#include "lvgl.h"
#include "lvgl_helpers.h"
//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief This function handles events that happen on LVGL buttons.
 *
 * @param [in] p_event Pointer to the event type.
 */
static void _button_event_handler(lv_event_t *p_event);

/**
 * @brief The function unblockingly sends an event to the user interface queue.
 *
 * @param event Gui event to be sent.
 */
static void _gui_app_event_send(gui_app_event_t event);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
lv_obj_t *p_btn1;
lv_obj_t *p_btn_led_on;
lv_obj_t *p_btn_led_off;

//------------------------------- GLOBAL DATA ---------------------------------
extern QueueHandle_t p_user_interface_queue;

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void gui_app_init(void)
{
    /* Create button 1 */
    lv_obj_t *p_label1;
    p_btn1 = lv_btn_create(lv_scr_act());
    lv_obj_align_to(p_btn1, NULL, LV_ALIGN_CENTER, 0, -80);
    p_label1 = lv_label_create(p_btn1);
    lv_label_set_text(p_label1, "Button 1");

    /* Add callback for button 1 */
    (void)lv_obj_add_event_cb(p_btn1, _button_event_handler, LV_EVENT_CLICKED, NULL);

    /* Create "led on" button */
    lv_obj_t *p_led_on_label;
    p_btn_led_on = lv_btn_create(lv_scr_act());
    lv_obj_align_to(p_btn_led_on, NULL, LV_ALIGN_LEFT_MID, 0, 0);
    p_led_on_label = lv_label_create(p_btn_led_on);
    lv_label_set_text(p_led_on_label, "LED on");

    /* Add callback for "led on" button */
    (void)lv_obj_add_event_cb(p_btn_led_on, _button_event_handler, LV_EVENT_CLICKED, NULL);

    /* Create "led off" button */
    lv_obj_t *p_led_off_label;
    p_btn_led_off = lv_btn_create(lv_scr_act());
    lv_obj_align_to(p_btn_led_off, NULL, LV_ALIGN_CENTER, 0, 0);
    p_led_off_label = lv_label_create(p_btn_led_off);
    lv_label_set_text(p_led_off_label, "LED off");

    /* Add callback for "led off" button */
    (void)lv_obj_add_event_cb(p_btn_led_off, _button_event_handler, LV_EVENT_CLICKED, NULL);
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _button_event_handler(lv_event_t *p_event)
{
    if(p_btn1 == p_event->target)
    {
        if(LV_EVENT_CLICKED == p_event->code)
        {
            printf("Button 1 clicked\n");
        }
    }
    else if(p_btn_led_on == p_event->target)
    {
        if(LV_EVENT_CLICKED == p_event->code)
        {
            /* Inform the user interface about button click. */
            _gui_app_event_send(GUI_APP_EVENT_BUTTON_LED_ON_PRESSED);
        }
    }
    else if(p_btn_led_off == p_event->target)
    {
        if(LV_EVENT_CLICKED == p_event->code)
        {
            /* Inform the user interface about button click. */
            _gui_app_event_send(GUI_APP_EVENT_BUTTON_LED_OFF_PRESSED);
        }
    }
    else
    {
        /* Unknown button event. */
    }
}

static void _gui_app_event_send(gui_app_event_t event)
{
    if(p_user_interface_queue != NULL)
    {
        xQueueSend(p_user_interface_queue, &event, 0U);
    }
}

//---------------------------- INTERRUPT HANDLERS -----------------------------
