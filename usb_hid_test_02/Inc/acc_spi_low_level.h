#ifndef INC_ACC_SPI_LOW_LEVEL_H_
#define INC_ACC_SPI_LOW_LEVEL_H_

#include "stdint.h"

void acc_spi_chipsel_low();
void acc_spi_chipsel_high();
uint8_t acc_spi_read_1byte(uint8_t address);
uint16_t acc_spi_write_2byte_word(uint16_t word16);

#endif /* INC_ACC_SPI_LOW_LEVEL_H_ */
