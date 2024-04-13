#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"

#define TAG "WIFI_PROV"

// BLE definitions
#define WIFI_PROV_SERVICE_UUID 0x00FF
#define WIFI_SSID_CHAR_UUID    0xFF01
#define WIFI_PASS_CHAR_UUID    0xFF02

// WiFi credentials
char ssid[32];
char password[64];

// Event handler for WiFi connection
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data) {
    if (event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_id == WIFI_EVENT_STA_CONNECTED) {
        ESP_LOGI(TAG, "Connected to AP");
    } else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGI(TAG, "Disconnected from AP");
    }
}

// BLE callback function
static void wifi_prov_ble_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t* param) {
    switch (event) {
        case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
            // Advertising data set complete event
            break;
        case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
            // Advertising start complete event
            break;
        case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
            // Advertising stop complete event
            break;
        case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
            // Scan response data set complete event
            break;
        case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
            // Raw advertising data set complete event
            break;
        case ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
            // Raw scan response data set complete event
            break;
        case ESP_GAP_BLE_ADV_START_EVT:
            // Advertising start event
            break;
        case ESP_GAP_BLE_ADV_STOP_EVT:
            // Advertising stop event
            break;
        case ESP_GAP_BLE_SCAN_RSP_RECVED_EVT:
            // Scan response received event
            break;
        default:
            break;
    }
}

// Initialize BLE
static void wifi_prov_init_ble() {
    ESP_ERROR_CHECK(esp_ble_gap_register_callback(wifi_prov_ble_cb));
    esp_ble_gap_config_adv_data_raw((uint8_t *)adv_data, sizeof(adv_data));
    esp_ble_gap_start_advertising(&adv_params);
}

// Task to handle WiFi provisioning
void wifi_prov_task(void *pvParameters) {
    // Initialize BLE
    wifi_prov_init_ble();

    // Loop to handle provisioning process
    while (1) {
        // Check if WiFi credentials are received via BLE
        if (wifi_credentials_received) {
            // Connect to the WiFi network
            wifi_config_t wifi_config = {
                .sta = {
                    .ssid = ssid,
                    .password = password
                },
            };
            esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
            esp_wifi_start();
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main() {
    // Initialize NVS
    ESP_ERROR_CHECK(nvs_flash_init());

    // Initialize TCP/IP stack
    tcpip_adapter_init();

    // Initialize WiFi
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL, NULL));

    // Create WiFi provisioning task
    xTaskCreate(&wifi_prov_task, "wifi_prov_task", 4096, NULL, 5, NULL);
}
