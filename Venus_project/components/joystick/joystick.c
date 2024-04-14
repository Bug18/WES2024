#include "joystick.h"
#include "driver/gpio.h"
#include <stdio.h>

#define JOY_X_PIN 34U
#define JOY_Y_PIN 35U

void init_joystick() {
    // Configure joystick pins as input
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << JOY_X_PIN) | (1ULL << JOY_Y_PIN);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
}

int read_joystick_x() {
    // Read joystick X position
    return gpio_get_level(JOY_X_PIN);
}

int read_joystick_y() {
    // Read joystick Y position
    return gpio_get_level(JOY_Y_PIN);
}

