#include <driver/gpio.h>
#include <step_driver.h>

// const uint8_t step_sequence_forward[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
// const uint8_t step_sequence_backward[4][4] = {{0, 0, 0, 1}, {0, 0, 1, 0}, {0, 1, 0, 0}, {1, 0, 0, 0}};

void step_driver_init(step_driver_t *driver, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t steps_per_rev) {
    driver->pin1 = pin1;
    driver->pin2 = pin2;
    driver->pin3 = pin3;
    driver->pin4 = pin4;
    driver->steps_per_rev = steps_per_rev;

    driver->current_step = 0;
    driver->current_millis = 0;

    gpio_pad_select_gpio(driver->pin1);
    gpio_pad_select_gpio(driver->pin2);
    gpio_pad_select_gpio(driver->pin3);
    gpio_pad_select_gpio(driver->pin4);

    gpio_set_direction(driver->pin1, GPIO_MODE_OUTPUT);
    gpio_set_direction(driver->pin2, GPIO_MODE_OUTPUT);
    gpio_set_direction(driver->pin3, GPIO_MODE_OUTPUT);
    gpio_set_direction(driver->pin4, GPIO_MODE_OUTPUT);

    gpio_set_level(driver->pin1, true);
    gpio_set_level(driver->pin2, false);
    gpio_set_level(driver->pin3, false);
    gpio_set_level(driver->pin4, false);
}

void step_driver_step(step_driver_t *driver, int steps) {}