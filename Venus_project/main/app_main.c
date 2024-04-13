/**
 * @file main.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2022 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "user_interface.h"
#include <esp_event.h>
#include <esp_log.h>
#include <esp_netif.h>
#include <esp_wifi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <nvs_flash.h>
#include <stdio.h>
#include <stdbool.h>
#include "Wifi.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

#define DELAY_TIME_MS (5000U) 

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void app_main(void)
{
    user_interface_init();

    esp_err_t err = ESP_OK;

    /* Initialize NVS partition */
    err = _nvs_init();

    if(ESP_OK == err)
    {
        /* Initialize TCP/IP */
        ESP_LOGI(TAG, " Initialize TCP/IP");
        err = esp_netif_init();
    }

    if(ESP_OK == err)
    {
        /* Initialize the event loop */
        ESP_LOGI(TAG, " Initialize the event loop");
        err = esp_event_loop_create_default();
    }

    if(ESP_OK == err)
    {
        /* Register our event handler for Wi-Fi and IP and related events */
        ESP_LOGI(TAG, " Register our event handler for Wi-Fi");
        err = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &_event_handler, NULL);
    }

    if(ESP_OK == err)
    {
        /* Register our event handler for Wi-Fi and IP and related events */
        ESP_LOGI(TAG, " Register our event handler for IP and related events");
        err = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &_event_handler, NULL);
    }

    if(ESP_OK == err)
    {
        /* Start the station */
        ESP_LOGI(TAG, " Start the station");
        err = _wifi_init_sta();
    }

    if(ESP_OK != err)
    {
        ESP_LOGE(TAG, "Init failed");
    }

    /* Do something */

    int index = 0;
    for(;;)
    {
        printf("[%d] WiFi Example!\n", index);
        index++;
        vTaskDelay(DELAY_TIME_MS / portTICK_PERIOD_MS);
    }
    
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------
