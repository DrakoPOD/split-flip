#ifndef STEP_DRIVER_H
#define STEP_DRIVER_H
#pragma once

#include <stdio.h>

typedef struct {
    uint8_t pin1;
    uint8_t pin2;
    uint8_t pin3;
    uint8_t pin4;
    uint8_t steps_per_rev;

    uint8_t current_step;
    uint8_t current_millis;
} step_driver_t;

void step_driver_init(step_driver_t *driver, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t steps_per_rev);
void step_driver_step(step_driver_t *driver, int steps);

#endif