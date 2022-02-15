#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>


#include "rpi.h"
#include "spi.h"
#include "fpga.h"
#include "ice40.h"

#include "driver/gpio.h"
#include <stdio.h>

// footprint is different for mosi and miso
#define S_MOSI GPIO_NUM_25  // GPIO 25
#define S_MISO GPIO_NUM_26  // GPIO 26
#define S_CLK GPIO_NUM_32   // GPIO 32
#define S_CE0 GPIO_NUM_27   // GPIO 27
#define S_HOLD GPIO_NUM_35  // GPIO 35
#define S_WP GPIO_NUM_34    // GPIO 34
#define S_D0 S_MOSI
#define S_D1 S_MISO
#define S_D2 S_WP
#define S_D3 S_HOLD
static unsigned int F_RESET = GPIO_NUM_1;  // GPIO 1
#define F_DONE GPIO_NUM_33  // GPIO 33



void initfomu(struct ff_spi *spi, struct ff_fpga *fpga){
    enum spi_type spi_type = ST_SINGLE;
    int spi_flash_bytes = -1;
 

    spiSetPin(spi, SP_CLK, S_CLK);
    spiSetPin(spi, SP_D0, S_D0);
    spiSetPin(spi, SP_D1, S_D1);
    spiSetPin(spi, SP_D2, S_D2);
    spiSetPin(spi, SP_D3, S_D3);
    spiSetPin(spi, SP_MISO, S_MISO);
    spiSetPin(spi, SP_MOSI, S_MOSI);
    spiSetPin(spi, SP_HOLD, S_HOLD);
    spiSetPin(spi, SP_WP, S_WP);
    spiSetPin(spi, SP_CS, S_CE0);

    // by default do not unlock the chip
    // spiSetUnlockCmd(spi, NO_UNLOCK_CMD);

    fpgaSetPin(fpga, FP_RESET, F_RESET);
    fpgaSetPin(fpga, FP_DONE, F_DONE);
    fpgaSetPin(fpga, FP_CS, S_CE0);

    // printf("Init devicest\n");


    fpgaInit(fpga);
    fpgaReset(fpga);
    spiInit(spi);

    spiSetType(spi, spi_type);

    if (spi_flash_bytes != -1)
        spiOverrideSize(spi, spi_flash_bytes);
}


void releasefomu(struct ff_spi *spi, struct ff_fpga *fpga){
    spiFree(&spi);
    fpgaFree(&fpga);    
}


void resetfpga(struct ff_fpga *fpga){
    printf("resetting fpga\n");
    fpgaResetMaster(fpga);
}


void memory_id(struct ff_spi *spi) {
    struct spi_id id = spiId(spi);
    printf("Manufacturer ID: %s (%02x)\n", id.manufacturer, id.manufacturer_id);
    if (id.manufacturer_id != id._manufacturer_id)
        printf("!! JEDEC Manufacturer ID: %02x\n",
        id._manufacturer_id);
    printf("Memory model: %s (%02x)\n", id.model, id.memory_type);
    printf("Memory size: %s (%02x)\n", id.capacity, id.memory_size);
    printf("Device ID: %02x\n", id.device_id);
    if (id.device_id != id.signature)
        printf("!! Electronic Signature: %02x\n", id.signature);
    printf("Serial number: %02x %02x %02x %02x\n", id.serial[0], id.serial[1], id.serial[2], id.serial[3]);
    printf("Status 1: %02x\n", spiReadStatus(spi, 1));
    printf("Status 2: %02x\n", spiReadStatus(spi, 2));
    printf("Status 3: %02x\n", spiReadStatus(spi, 3));
}
