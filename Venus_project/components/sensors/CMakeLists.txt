idf_component_register(SRCS "sensors.c"
                    INCLUDE_DIRS "include"
                    REQUIRES sht31 accel led ui log Buzzer_signaling mqtt_driver eeprom_driver)
