#include <stdio.h>

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "led_strip_types.h"

#define DRIVER_PIN1 4
#define DRIVER_PIN2 5
#define DRIVER_PIN3 6
#define DRIVER_PIN4 7

uint8_t current_step = 0;

// turn off led strip

void step(bool forward) {
    if (forward) {
        switch (current_step) {
            case 0:
                gpio_set_level(DRIVER_PIN1, true);
                gpio_set_level(DRIVER_PIN2, false);
                gpio_set_level(DRIVER_PIN3, false);
                gpio_set_level(DRIVER_PIN4, false);
                break;
            case 1:
                gpio_set_level(DRIVER_PIN1, false);
                gpio_set_level(DRIVER_PIN2, true);
                gpio_set_level(DRIVER_PIN3, false);
                gpio_set_level(DRIVER_PIN4, false);
                break;
            case 2:
                gpio_set_level(DRIVER_PIN1, false);
                gpio_set_level(DRIVER_PIN2, false);
                gpio_set_level(DRIVER_PIN3, true);
                gpio_set_level(DRIVER_PIN4, false);
                break;
            case 3:
                gpio_set_level(DRIVER_PIN1, false);
                gpio_set_level(DRIVER_PIN2, false);
                gpio_set_level(DRIVER_PIN3, false);
                gpio_set_level(DRIVER_PIN4, true);
                break;
        }
    } else {
        switch (current_step) {
            case 0:
                gpio_set_level(DRIVER_PIN1, false);
                gpio_set_level(DRIVER_PIN2, false);
                gpio_set_level(DRIVER_PIN3, false);
                gpio_set_level(DRIVER_PIN4, true);
                break;
            case 1:
                gpio_set_level(DRIVER_PIN1, false);
                gpio_set_level(DRIVER_PIN2, false);
                gpio_set_level(DRIVER_PIN3, true);
                gpio_set_level(DRIVER_PIN4, false);
                break;
            case 2:
                gpio_set_level(DRIVER_PIN1, false);
                gpio_set_level(DRIVER_PIN2, true);
                gpio_set_level(DRIVER_PIN3, false);
                gpio_set_level(DRIVER_PIN4, false);
                break;
            case 3:
                gpio_set_level(DRIVER_PIN1, true);
                gpio_set_level(DRIVER_PIN2, false);
                gpio_set_level(DRIVER_PIN3, false);
                gpio_set_level(DRIVER_PIN4, false);
                break;
        }
    }

    current_step = (current_step + 1) % 4;
}

void app_main(void) {
    esp_rom_gpio_pad_select_gpio(DRIVER_PIN1);
    esp_rom_gpio_pad_select_gpio(DRIVER_PIN2);
    esp_rom_gpio_pad_select_gpio(DRIVER_PIN3);
    esp_rom_gpio_pad_select_gpio(DRIVER_PIN4);

    gpio_set_direction(DRIVER_PIN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(DRIVER_PIN2, GPIO_MODE_OUTPUT);
    gpio_set_direction(DRIVER_PIN3, GPIO_MODE_OUTPUT);
    gpio_set_direction(DRIVER_PIN4, GPIO_MODE_OUTPUT);

    gpio_set_level(DRIVER_PIN1, true);
    gpio_set_level(DRIVER_PIN2, false);
    gpio_set_level(DRIVER_PIN3, false);
    gpio_set_level(DRIVER_PIN4, false);

    while (true) {
        step(true);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
