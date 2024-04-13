/**
 * @file app_main.c
 *
 * @brief WiFi station mode example.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include <esp_event.h>
#include <esp_log.h>
#include <esp_netif.h>
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <stdio.h>
#include "WiFi.h"

//---------------------------------- MACROS -----------------------------------
#define SSID ("ZICER-guest")
#define PASS ("Z1c3r.10020")

#define DELAY_TIME_MS (5000U)

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------

//---------------------------- PRIVATE FUNCTIONS ------------------------------

esp_err_t _wifi_init_sta(void)
{
    esp_err_t err = ESP_OK;

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    err = esp_wifi_init(&cfg);

    if(ESP_OK == err)
    {
        ESP_LOGI(TAG, "Set wifi credentials storage: RAM");
        err = esp_wifi_set_storage(WIFI_STORAGE_RAM);
    }

    if(ESP_OK == err)
    {
        ESP_LOGI(TAG, "Set wifi mode: STATION");
        err = esp_wifi_set_mode(WIFI_MODE_STA);
    }

    wifi_config_t wifi_config = 
    {
      .sta =
          {
              .ssid = SSID,
              .password = PASS,
          },
    };

    if(ESP_OK == err)
    {
        ESP_LOGI(TAG, "Configure wifi");
        err = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    }

    if(ESP_OK == err)
    {
        err = esp_wifi_start();
        ESP_LOGI(TAG, "Try to connect to AP with SSID:%s PSWD:%s", SSID, PASS);
    }

    return err;
}

esp_err_t _nvs_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if((ESP_ERR_NVS_NO_FREE_PAGES == ret) || (ESP_ERR_NVS_NEW_VERSION_FOUND == ret))
    {
        /* NVS partition was truncated
         * and needs to be erased */
        ret = nvs_flash_erase();

        /* Retry nvs_flash_init */
        ret |= nvs_flash_init();
    }
    return ret;
}

//---------------------------- INTERRUPT HANDLERS -----------------------------

void _event_handler(void *p_arg, esp_event_base_t event_base, int32_t event_id, void *p_event_data)
{
    // TODO: add provisioning


    if((WIFI_EVENT == event_base) && (WIFI_EVENT_STA_START == event_id))
    {
        ESP_LOGI(TAG, "Try to connect.");
        esp_wifi_connect();
    }
    else if((IP_EVENT == event_base) && (IP_EVENT_STA_GOT_IP == event_id))
    {
        ip_event_got_ip_t *p_event = (ip_event_got_ip_t *)p_event_data;
        ESP_LOGI(TAG, "CONNECTED with IP Address:" IPSTR, IP2STR(&p_event->ip_info.ip));
        /* Signal main application to continue execution */
    }
    else if((WIFI_EVENT == event_base) && (WIFI_EVENT_STA_DISCONNECTED == event_id))
    {
        ESP_LOGI(TAG, "DISCONNECTED. \nReconnecting to the AP again...");
        esp_wifi_connect();
    }
}
