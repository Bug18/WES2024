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
// #include "provisioning.h"
#include "mqtt_driver.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

#define DELAY_TIME_MS (5000U) 

void app_main(void)
{
    user_interface_init();
    
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI("WIFI", "ESP_WIFI_MODE_STA");
    wifi_init_sta();

    ESP_LOGI("MQTT", "[APP] Startup..");
    ESP_LOGI("MQTT", "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
    ESP_LOGI("MQTT", "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("mqtt_client", ESP_LOG_VERBOSE);
    esp_log_level_set("mqtt_example", ESP_LOG_VERBOSE);
    esp_log_level_set("transport_base", ESP_LOG_VERBOSE);
    esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
    esp_log_level_set("transport", ESP_LOG_VERBOSE);
    esp_log_level_set("outbox", ESP_LOG_VERBOSE);

    // ESP_ERROR_CHECK(nvs_flash_init());
    // ESP_ERROR_CHECK(esp_netif_init());
    // ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    // ESP_ERROR_CHECK(example_connect());

    // vTaskDelay(DELAY_TIME_MS / portTICK_PERIOD_MS);

    esp_mqtt_client_handle_t *client = mqtt_app_start();

    float acc[3] = {3.0f, 2.0f, 1.0f};
    float temp = 25.2f;
    float hum = 55.5f;

    send_sensor_message(client, temp, hum, acc);

    /* Do something */

    int index = 0;
    for(;;)
    {
        // if (index == 1000){
        //     err = _wifi_disconnect();

        //     if (err == ESP_OK){
        //         printf("Disconnect succesful");
        //         break;
        //     } else {
        //         printf("Disconnect unsuccesful!");
        //     }
        // }
        printf("[%d] WiFi Example!\n", index);
        index++;
        vTaskDelay(DELAY_TIME_MS / portTICK_PERIOD_MS);
    }
}
