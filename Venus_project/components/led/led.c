/**
 * @file led.c
 *
 * @brief This file controls LEDs.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "led.h"
#include "driver/gpio.h"
#include <stdio.h>
#include <stdbool.h>

//---------------------------------- MACROS -----------------------------------
#define GPIO_BIT_MASK(X) ((1ULL << (X)))

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief LED config structure.
 *
 */
typedef struct
{
    led_t  led;
    int8_t gpio;
    bool   b_is_active_on_high_level;
} _led_config_t;

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static const _led_config_t _led_info[LED_COUNT] = {
    { .led = LED_BLUE, .gpio = 14, .b_is_active_on_high_level = true },
    { .led = LED_GREEN, .gpio = 27, .b_is_active_on_high_level = true},
    { .led = LED_RED, .gpio = 26, .b_is_active_on_high_level = true},
};

QueueHandle_t ledEventQueue;

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
esp_err_t led_init(led_t led)
{
    esp_err_t esp_err = ESP_OK;

    if(led < LED_COUNT)
    {
        /* Zero-initialize the config structure. */
        gpio_config_t io_conf = {};
        /* Disable interrupt. */
        io_conf.intr_type = GPIO_INTR_DISABLE;
        /* Set as output. */
        io_conf.mode = GPIO_MODE_OUTPUT;
        /* Bit mask of the pins that you want to set,e.g.GPIO18/19. */
        io_conf.pin_bit_mask = GPIO_BIT_MASK(_led_info[led].gpio);
        /* Disable internal pull-down. */
        io_conf.pull_down_en = 0;
        /* Disable internal pull-up. */
        io_conf.pull_up_en = 0;
        /* Configure GPIO with the given settings. */
        gpio_config(&io_conf);
    }
    else
    {
        esp_err = ESP_FAIL;
    }

    return esp_err;
}

esp_err_t led_on(led_t led)
{
    esp_err_t esp_err = ESP_FAIL;

    if(led < LED_COUNT)
    {
        /* Figure out if the LED will turn on after outputting 1 or 0. */
        uint32_t level = _led_info[led].b_is_active_on_high_level ? 1U : 0U;

        esp_err = gpio_set_level(_led_info[led].gpio, level);
    }

    return esp_err;
}

esp_err_t led_off(led_t led)
{
    esp_err_t esp_err = ESP_FAIL;

    if(led < LED_COUNT)
    {
        /* Figure out if the LED will turn off after outputting 1 or 0. */
        uint32_t level = _led_info[led].b_is_active_on_high_level ? 0U : 1U;

        esp_err = gpio_set_level(_led_info[led].gpio, level);
    }

    return esp_err;
}


//LED signalization 
static void _led_task(void *p_parametar)
{
    while(1) {
        _led_event_t event;
        if (xQueueReceive(ledEventQueue, &event, portMAX_DELAY) == pdFALSE){
            //ESP_LOGE(pcTaskGetName(NULL), "Couldn't recieve next action from queue...  Too much wait or internal error");
            continue;
        }

        for(int i = 0; i < event.count; i ++)
        {
            led_on(event.led);
            vTaskDelay(event.delay_on/ portTICK_PERIOD_MS); 

            led_off(event.led);
            vTaskDelay(event.delay_off / portTICK_PERIOD_MS); 
        }

    }
}

void _led_task_init()
{
    //stvaranje queue-a za led events
    ledEventQueue = xQueueCreate(10, sizeof(_led_event_t));
    if (ledEventQueue == NULL) {
        printf("Failed to create led event queue");
    }

    //inicijalizacija ledica
    for(int i = 0; i < LED_COUNT; i ++) {
        led_init(_led_info[i].led);
    }

    xTaskCreate(&_led_task, "led_task", 2 * 1024, NULL, 5, NULL);
}


void led_queue_message(_led_event_t *event){
    xQueueSend(ledEventQueue, event, pdMS_TO_TICKS(500));
}

void led_queue_blue_led(){
    _led_event_t blue_event = {
        .led = LED_BLUE,
        .delay_on = 800,
        .delay_off = 200,
        .count = 1
    };
    xQueueSend(ledEventQueue, &blue_event, pdMS_TO_TICKS(500));
}


//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
