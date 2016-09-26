#ifndef INC_SPI_LOW_LEVEL_H_
#define INC_SPI_LOW_LEVEL_H_
//-------------------------------------------------

#include "mxconstants.h"
#include "stdint.h"

extern int new_frame_ready_flag;

#define CHIPSEL spi1_chipsel_Pin

uint32_t wait_for_drdy(void);
void synchronize(void);

//returns chipsel pin port current content
uint32_t chipsel_high(void);
uint32_t chipsel_low(void);

// writes byte, returns content of spi->dr
uint16_t write_2byte_word(uint16_t word16);
uint16_t read_2byte_word(void);
// writes word, returns content of spi->dr
uint32_t write_4byte_word(uint32_t word32);     // word - 4 bytes
uint32_t read_4byte_word(void);  // word - 4 bytes

//-------------------------------------------------
#endif /* INC_SPI_LOW_LEVEL_H_ */
