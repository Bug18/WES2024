#include "sensors.h"

void welcome_jingle() {
    _led_event_t led_setup_r = {
        .led = LED_RED,
        .delay_off = 0,
        .delay_on = 250,
        .count = 1
    };
    led_queue_message(&led_setup_r);

    _led_event_t led_setup_g = {
        .led = LED_GREEN,
        .delay_off = 0,
        .delay_on = 250,
        .count = 1
    };
    led_queue_message(&led_setup_g);

    _led_event_t led_setup_b = {
        .led = LED_BLUE,
        .delay_off = 0,
        .delay_on = 250,
        .count = 1
    };
    led_queue_message(&led_setup_b);

    buzzer_send_signal_IRQ(WELCOME);
}

void sensors_task(void *params) {
    //vTaskDelay(10000 / portTICK_PERIOD_MS);
    int message_id;

    char array[32];

    // EARTHQUAKE
    char has_tested = 0; 
    float past_Z_acc = 0;

    // STARTUP JINGLE
    welcome_jingle();

    while(1) {
        float acc[3] = {0.f, 0.f, 0.f};
        int accel_status = accel_read_polling(acc);

        if (accel_status != 0) {
            ESP_LOGE(pcTaskGetName(NULL), "Couldn't read accelerometer!");
        } else {
            sprintf(array, "Acc (X):          %0.2f", acc[0]);
            lv_label_set_text(ui_Accelerometer, array);

            sprintf(array, "Acc (Y):          %0.2f", acc[1]);
            lv_label_set_text(ui_Accelerometer1, array);

            sprintf(array, "Acc (Z):          %0.2f", acc[2]);
            lv_label_set_text(ui_Accelerometer2, array);

            if(has_tested && fabs(past_Z_acc - acc[2]) > 0.2) {
                buzzer_send_signal(SOS);

                _led_event_t led_setup = {
                    .led = LED_RED,
                    .delay_off = 100,
                    .delay_on = 100,
                    .count = 10
                };
                led_queue_message(&led_setup);

            } else {
                has_tested = 1;
            }

            past_Z_acc = acc[2];
        }

        float temp = 0.f;
        float humid = 0.f;

        esp_err_t humid_temp_status = sht31_read_temp_humi(&temp, &humid);

        if (humid_temp_status != ESP_OK) {
            ESP_LOGE(pcTaskGetName(NULL), "Couldn't read shit sensor!");
        } else {
            sprintf(array, "Temperature:    %0.2f°C", temp);
            lv_label_set_text(ui_Temperature, array);

            sprintf(array, "Humidity:      %0.2f", humid);
            lv_label_set_text(ui_Humidity, array);
        }
        
        message_id = send_sensor_message(temp, humid, acc);

        if (message_id == -1){
            printf("Message publish failed");
        }else{
            printf("Message succesfully published");
        }

        // writing to eeprom
        eeprom_write(0x50, 0x00, (uint8_t)temp, sizeof(temp));
        
        led_queue_blue_led();
        vTaskDelay(1000 / portTICK_PERIOD_MS); 
    }
}

void sensors_init() {
    sht31_init();
    accel_init();

    xTaskCreate(&sensors_task, "sensors", 5 * 1024, NULL, 5, NULL);
}