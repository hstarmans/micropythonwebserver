#ifndef _FOMU_H
#define _FOMU_H

#include "spi.h"
#include "fpga.h"

void initfomu(struct ff_spi *spi, struct ff_fpga *fpga);
void releasefomu(struct ff_spi *spi, struct ff_fpga *fpga);
void resetfpga(struct ff_fpga *fpga);
void memory_id(struct ff_spi *spi);
void write_bin(struct ff_spi *spi, const char *op_filename);


#endif /* FOMU_H_ */
