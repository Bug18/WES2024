idf_component_register(SRCS "mqtt_driver.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_event freertos esp_netif esp_wifi nvs_flash mqtt json)
