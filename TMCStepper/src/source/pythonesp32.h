#pragma once
#include "driver/gpio.h"

#define INPUT GPIO_MODE_INPUT
#define INPUT_PULLUP GPIO_MODE_INPUT
#define INPUT_PULLDOWN GPIO_MODE_INPUT
#define OUTPUT GPIO_MODE_INPUT_OUTPUT

#define HIGH 1
#define LOW 0

#define pinMode(PIN, MODE) gpio_set_direction((gpio_num_t)PIN, MODE)
#define digitalWrite(PIN, MODE) gpio_set_level((gpio_num_t)PIN, MODE)
#define digitalRead(PIN)  gpio_get_level((gpio_num_t)PIN)
