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
#include "mqtt_driver.h"
#include "led.h"
#include "sensors.h"
#include "Buzzer_signaling.h"
#include "eeprom_driver.h"

#define DELAY_TIME_MS (5000U) 


void app_main(void)
{
    /*----------------------------Intialization----------------------------*/

    // Initialize user interface on onboard screen
    user_interface_init();
    
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize WiFi
    ESP_LOGI("WIFI", "ESP_WIFI_MODE_STA");
    wifi_init_sta();


    // Initialize MQTT
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

    vTaskDelay(2000 / portTICK_PERIOD_MS); 

    // Initialize LEDs
    _led_task_init();

    // Initalize buzzer
    buzzer_init();

    // Initialize sensors
    sensors_init();

    // ESP_ERROR_CHECK(example_connect());
    // vTaskDelay(DELAY_TIME_MS / portTICK_PERIOD_MS);

    // Start MQTT
    mqtt_app_start();
    
    /*----------------------------End of Intialization----------------------------*/

    


















    // float acc[3] = {5.0f, -5.0f, 5.0f};
    // float temp = 23.2f;
    // float hum = 53.9f;

    // int message_id;

    // message_id = send_sensor_message(client, temp, hum, acc);

    // if (message_id == -1){
    //     printf("Message publish failed");
    // }else{
    //     printf("Message succesfully published");
    // }

    // /* Do something */
    // esp_err_t err = ESP_OK;
    // int index = 0;
    // for(;;)
    // {
    //     if (index == 3){
    //         err = disconnect_wifi();

    //         if (err == ESP_OK){
    //             printf("Disconnect succesful");
    //             break;
    //         } else {
    //             printf("Disconnect unsuccesful!");
    //         }
    //     }
    //     printf("[%d] WiFi Example!\n", index);
    //     index++;
    //     vTaskDelay(DELAY_TIME_MS / portTICK_PERIOD_MS);
    // }
}
