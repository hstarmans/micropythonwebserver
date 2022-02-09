#include <stdio.h>
#include <stdint.h>
#include "driver/gpio.h"

void gpioSetMode(unsigned gpio, unsigned mode) {
   gpio_pad_select_gpio(gpio);
   gpio_set_direction(gpio, mode);
}

int gpioRead(unsigned gpio) {
   return gpio_get_level(gpio);
}

void gpioWrite(unsigned gpio, unsigned level) {
   gpio_set_level(gpio, level);
}
