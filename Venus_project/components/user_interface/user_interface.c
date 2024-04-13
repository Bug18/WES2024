/**
 * @file user_interface.c
 *
 * @brief This file is responsible for complete user interface (LEDs, buttons
 * and GUI).
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "user_interface.h"
#include "led.h"
#include "gui.h"
#include "gui_app.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <stdio.h>

//---------------------------------- MACROS -----------------------------------
#define USER_INTERFACE_QUEUE_SIZE (20U)
//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief User inteface task.
 *
 * @param [in] p_parameter This is the parameter that is passed to the task.
 */
static void _user_interface_task(void *p_parameter);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static TaskHandle_t p_user_interface_task = NULL;

//------------------------------- GLOBAL DATA ---------------------------------
QueueHandle_t p_user_interface_queue = NULL;

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void user_interface_init(void)
{
    led_init(LED_BLUE);
    gui_init();

    p_user_interface_queue = xQueueCreate(USER_INTERFACE_QUEUE_SIZE, sizeof(gui_app_event_t));
    if(p_user_interface_queue == NULL)
    {
        printf("User interface queue was not initialized successfully\n");
        return;
    }

    if(pdPASS != xTaskCreate(&_user_interface_task, "user_interface_task", 2 * 1024, NULL, 5, &p_user_interface_task))
    {
        printf("User interface task was not initialized successfully\n");
        return;
    }
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _user_interface_task(void *p_parameter)
{
    gui_app_event_t gui_event;

    for(;;)
    {
        /* Blockingly wait on an event. */
        if((p_user_interface_queue != NULL) && (xQueueReceive(p_user_interface_queue, &gui_event, portMAX_DELAY) == pdTRUE))
        {
            printf("GUI event received %d\n", gui_event);

            switch(gui_event)
            {
                case GUI_APP_EVENT_BUTTON_LED_ON_PRESSED:
                    led_on(LED_BLUE);
                    break;

                case GUI_APP_EVENT_BUTTON_LED_OFF_PRESSED:
                    led_off(LED_BLUE);
                    break;
                default:
                    printf("Uknown GUI event\n");
                    break;
            }
        }
    }
}

//---------------------------- INTERRUPT HANDLERS -----------------------------
