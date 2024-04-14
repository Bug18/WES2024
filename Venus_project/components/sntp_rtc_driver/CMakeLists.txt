idf_component_register(SRCS "sntp_rtc_driver.c"
                    INCLUDE_DIRS "include"
                    REQUIRES freertos nvs_flash esp_netif ui)
