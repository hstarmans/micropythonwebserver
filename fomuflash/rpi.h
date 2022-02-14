#ifndef RPI_H_
#define RPI_H_

#include "driver/gpio.h"
/* gpio modes. */
#define PI_INPUT  GPIO_MODE_INPUT
#define PI_OUTPUT GPIO_MODE_INPUT_OUTPUT

void gpioSetMode(unsigned gpio, unsigned mode);
int gpioRead(unsigned gpio);
void gpioWrite(unsigned gpio, unsigned level);

#endif /* RPI_H_ */
