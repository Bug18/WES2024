idf_component_register(SRCS "sntp_rtc_driver.c"
                    INCLUDE_DIRS "include"
                    REQUIRES freertos nvs_flash protocol_examples_common esp_netif ui)
