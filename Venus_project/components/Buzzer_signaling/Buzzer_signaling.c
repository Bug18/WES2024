#include "Buzzer_signaling.h"

QueueHandle_t buzzerEventQueue;

static void buzzer_gpio_init()
{   
   // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 4 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

static void buzzer_set(uint8_t state) {
    if (state)
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY);
    else
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);

    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

static void morse_dot() {
    buzzer_set(1);
    vTaskDelay(pdMS_TO_TICKS(100));
    buzzer_set(0);
    vTaskDelay(pdMS_TO_TICKS(300));
}

static void morse_line() {
    buzzer_set(1);
    vTaskDelay(pdMS_TO_TICKS(300));
    buzzer_set(0);
    vTaskDelay(pdMS_TO_TICKS(300));
}

static void sos_sound() {
    
    // S => . . .
    for(int i = 0; i < 3; i++){
        morse_dot();
    }

    // O => - - -
    for(int i = 0; i < 3; i++){
        morse_line();
    }

    // S => . . .
    for(int i = 0; i < 3; i++){
        morse_dot();
    }

}

static void welcome_sound() {
    morse_dot();
    morse_line();
    morse_dot();
}

void buzzer_task(void *pvParameters) {
    buzzer_gpio_init();

    while(1) {

        /*

        // TEST PATTERN

        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        
        vTaskDelay(pdMS_TO_TICKS(2000));

        ESP_LOGI(pcTaskGetName(NULL), "Cycle...");

        */

        buzzer_signal_enum_t event;
        if(xQueueReceive(buzzerEventQueue, &event, portMAX_DELAY) == pdFALSE){
            ESP_LOGE(pcTaskGetName(NULL), "Couldn't recieve next action from queue...  Too much wait or internal error");
            continue;
        }

        switch(event) {
            case SOS:
                sos_sound();
                break;

            case WELCOME:
                welcome_sound();
                break;
            
            default:
                break;
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void buzzer_send_signal(buzzer_signal_enum_t event) {
    xQueueSend(buzzerEventQueue, &event, pdMS_TO_TICKS(500));
}

void buzzer_init() {
    buzzerEventQueue = xQueueCreate(BUZEZR_MAX_QUEUE_LEN, sizeof(buzzer_signal_enum_t));
    if (buzzerEventQueue == NULL) {
        ESP_LOGE(pcTaskGetName(NULL), "Failed to create the LORA status queue");
    }

    xTaskCreate(&buzzer_task, "buzzer_task", 1024*2, NULL, 2, NULL);
}
