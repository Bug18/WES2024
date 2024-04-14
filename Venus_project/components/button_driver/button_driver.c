#include <stdio.h>
#include "button_driver.h"

static void _btn_1_isr(void *p_arg){
    buzzer_send_signal_IRQ(SOS);
}

static void _btn_2_isr(void *p_arg){
    _ui_screen_change(&ui_MainScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_MainScreen_screen_init);
}

static void _btn_3_isr(void *p_arg){
    // buzzer_send_signal_IRQ(WELCOME);
    _ui_screen_change(&ui_JoystickScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_JoystickScreen_screen_init);
}

static void _btn_4_isr(void *p_arg){
    _ui_screen_change(&ui_InfoScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_InfoScreen_screen_init);
}

static esp_err_t _button_init(uint8_t pin, button_pressed_isr_t p_isr)
{
    // Configure the GPIO.
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << pin),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = (GPIO_INTR_POSEDGE),
    };

    esp_err_t esp_err = gpio_config(&io_conf);

    if(ESP_OK == esp_err)
    {
        // Change gpio interrupt type for a pin.
        esp_err = gpio_set_intr_type(io_conf.pin_bit_mask, io_conf.intr_type);
    }

    if(ESP_OK == esp_err)
    {
        // Install gpio isr service.
        gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);
        /* esp_err is not assigned to it because it returns invalid
        statuses when called many times (for many buttons)*/
    }

    if(ESP_OK == esp_err)
    {
        // Hook isr handler for specific gpio pin.
        esp_err = gpio_isr_handler_add(pin, p_isr, (void *)&pin);
    }

    return esp_err;
}

void button_setup() {
    _button_init(GPIO_BUTTON_1, _btn_1_isr);
    _button_init(GPIO_BUTTON_2, _btn_2_isr);
    _button_init(GPIO_BUTTON_3, _btn_3_isr);
    _button_init(GPIO_BUTTON_4, _btn_4_isr);
}
