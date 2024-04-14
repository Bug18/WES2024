#pragma once

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <esp_event.h>

#include "ui.h"
#include "Buzzer_signaling.h"

#define GPIO_BUTTON_1 (36U)
#define GPIO_BUTTON_2 (32U)
#define GPIO_BUTTON_3 (33U)
#define GPIO_BUTTON_4 (25U)

typedef void (*button_pressed_isr_t)(void *p_arg);

void button_setup();
