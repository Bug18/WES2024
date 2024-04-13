idf_component_register(SRCS "WiFi.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_event freertos esp_netif esp_wifi nvs_flash lwip esp_bt)
