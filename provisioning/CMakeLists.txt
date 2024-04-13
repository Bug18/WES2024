idf_component_register(SRCS "provisioning.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_event freertos esp_netif esp_wifi nvs_flash wifi_provisioning)
