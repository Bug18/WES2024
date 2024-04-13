/**
 * @file led.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __LED_C__
#define __LED_C__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <stdio.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief Enums hold all board LEDs.
 *
 */

#define LED_COUNT 3

typedef enum
{
    LED_BLUE,
    LED_GREEN,
    LED_RED,
} led_t;


typedef struct
{
    led_t  led;
    uint16_t delay_on;
    uint16_t delay_off;
    uint16_t count;
} _led_event_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief The function initializes LED.
 *
 * @param [in] led LED instance (e.g. LED_BLUE).
 *
 * @return esp_err_t ESP_OK on success, fail otherwise.
 */
esp_err_t led_init(led_t led);

/**
 * @brief The function turns LED on.
 *
 * @param [in] led LED instance (e.g. LED_BLUE).
 *
 * @return esp_err_t ESP_OK on success, fail otherwise.
 */
esp_err_t led_on(led_t led);

/**
 * @brief The function turns LED off.
 *
 * @param [in] led LED instance (e.g. LED_BLUE).
 *
 * @return esp_err_t ESP_OK on success, fail otherwise.
 */
esp_err_t led_off(led_t led);


//Inicijalizacija ledica i stvaranje led queue-a
void _led_task_init();

//dodavanje led eventa u led queue
void led_queue_message(_led_event_t *event);

//dodavanje blinkanja blue ledice (LED signalizacija iz zadatka)
void led_queue_blue_led();

#ifdef __cplusplus
}
#endif

#endif // __LED_C__
