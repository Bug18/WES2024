idf_component_register(SRCS "joystick.c"
                    INCLUDE_DIRS "include"
                    REQUIRES driver freertos ui esp_adc log soc)
