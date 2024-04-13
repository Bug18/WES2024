#include "sensors.h"

void sensors_task(void *params) {
    //vTaskDelay(10000 / portTICK_PERIOD_MS);

    // EARTHQUAKE
    char has_tested = 0; 
    float past_Z_acc = 0;

    while(1) {

        float acc[3];
        int accel_status = accel_read_polling(acc);

        if (accel_status != 0) {
            ESP_LOGE(pcTaskGetName(NULL), "Couldn't read accelerometer!");
        } else {
            // TODO - push mqtt

            char Acc_X[32];
            sprintf(Acc_X, "Acc (X):          %0.2f", acc[0]);
            lv_label_set_text(ui_Accelerometer, Acc_X);

            char Acc_Y[32];
            sprintf(Acc_Y, "Acc (Y):          %0.2f", acc[1]);
            lv_label_set_text(ui_Accelerometer1, Acc_Y);

            char Acc_Z[32];
            sprintf(Acc_Z, "Acc (Z):          %0.2f", acc[2]);
            lv_label_set_text(ui_Accelerometer2, Acc_Z);

            if(has_tested && fabs(past_Z_acc - acc[2]) > 100) {
                buzzer_send_signal(SOS);
            } else {
                has_tested = 1;
            }

            past_Z_acc = acc[2];
        }

        float temp;
        float humid;

        esp_err_t humid_temp_status = sht31_read_temp_humi(&temp, &humid);

        if (humid_temp_status != ESP_OK) {
            ESP_LOGE(pcTaskGetName(NULL), "Couldn't read shit sensor!");
        } else {
            // TODO -> mqtt send

            char temp_str[32];
            sprintf(temp_str, "Temperature:    %0.2f°C", temp);
            lv_label_set_text(ui_Temperature, temp_str);

            char humid_str[32];
            sprintf(humid_str, "Humidity:      %0.2f", humid);
            lv_label_set_text(ui_Humidity, humid_str);
        }

        led_queue_blue_led();
        vTaskDelay(1000 / portTICK_PERIOD_MS); 
    }
}

void sensors_init() {
    sht31_init();
    accel_init();

    xTaskCreate(&sensors_task, "led_task", 2 * 1024, NULL, 5, NULL);
}