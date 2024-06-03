#include <stdio.h>

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "led_strip_types.h"

#define RGB_LED 48
#define MAX_LED 1

static const char *TAG = "flip-flap";

led_strip_handle_t led_strip;

led_strip_config_t strip_config = {
    .strip_gpio_num = RGB_LED,
    .max_leds = MAX_LED,
    .led_pixel_format = LED_PIXEL_FORMAT_GRB,
    .led_model = LED_MODEL_WS2812,
    .flags =
        {
            .invert_out = 0,
        },
};

led_strip_rmt_config_t rmt_config = {
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
    .rmt_channel = 0,
#else
    .clk_src = RMT_CLK_SRC_DEFAULT,
    .resolution_hz = 10 * 1000 * 1000,
    .flags.with_dma = false,
#endif
};

struct rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct rgb hue = {255, 0, 0};

char current_color = 'r';
bool maxed = false;

void change_color(void *pvParameter) {
    while (1) {
        switch (current_color) {
            case 'r':
                if (hue.g < 255 && !maxed) {
                    hue.g++;
                } else {
                    maxed = true;
                    hue.r--;
                    if (hue.r == 0) {
                        current_color = 'g';
                        maxed = false;
                    }
                }
                break;
            case 'g':
                if (hue.b < 255 && !maxed) {
                    hue.b++;
                } else {
                    maxed = true;
                    hue.g--;
                    if (hue.g == 0) {
                        current_color = 'b';
                        maxed = false;
                    }
                }
                break;
            case 'b':
                if (hue.r < 255 && !maxed) {
                    hue.r++;
                } else {
                    maxed = true;
                    hue.b--;
                    if (hue.b == 0) {
                        current_color = 'r';
                        maxed = false;
                    }
                }
                break;
        }

        led_strip_set_pixel(led_strip, 0, hue.r, hue.g, hue.b);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void blink_rgb(void *pvParameter) {
    ESP_LOGI(TAG, "Blinking RGB");
    while (1) {
        ESP_LOGI(TAG, "Blinking Green");
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 0, 0, 255, 0));
        ESP_ERROR_CHECK(led_strip_refresh(led_strip));
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG, "Blinking Blue");
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 0, 0, 0, 255));
        ESP_ERROR_CHECK(led_strip_refresh(led_strip));
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG, "Blinking Red");
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 0, 255, 0, 0));
        ESP_ERROR_CHECK(led_strip_refresh(led_strip));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void) {
    ESP_LOGI(TAG, "Initializing LED strip");
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));

    // xTaskCreate(&blink_rgb, "blink_rgb", 2048, NULL, 5, NULL);
    xTaskCreate(&change_color, "change_color", 2048, NULL, 5, NULL);
}
