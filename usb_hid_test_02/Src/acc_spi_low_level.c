#include "acc_spi_low_level.h"
#include "gpio.h"


void acc_spi_chipsel_low()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
}
void acc_spi_chipsel_high()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}



uint8_t acc_spi_read_1byte(uint8_t address)
{
	long i;

	uint16_t out_data = (((uint16_t)address)<<8)|0x8000; //address with first RW bit for read mode
	uint16_t return_value;

	// set chipselect low (start spi communication)
	acc_spi_chipsel_low();

	//check if a receiver buffer is full (have not read any old data)
	if ((SPI2->SR & SPI_SR_RXNE) != RESET )
		return_value = SPI2->DR; // read
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = out_data; // send

	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	return_value = SPI2->DR; // read

	// pause
	for(i=0; i<5; i++);
	// set chipselect high (stop spi communication)
	acc_spi_chipsel_high();
	//pause
	for(i=0; i<3; i++);

	return (uint8_t)return_value;
}

uint16_t acc_spi_write_2byte_word(uint16_t word16)
{
	long i;
	uint16_t in_data = 0x0000;
	uint16_t return_value;
	return_value = word16;

	// set chipselect low (start spi communication)
	acc_spi_chipsel_low();

	//check if a receiver buffer is full (have not read any old data)
	if ((SPI2->SR & SPI_SR_RXNE) != RESET )
		in_data = SPI2->DR; // read
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = word16; // send


	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI2->DR; // read

	// pause
	for(i=0; i<5; i++);
	// set chipselect high (stop spi communication)
	acc_spi_chipsel_high();
	//pause
	for(i=0; i<3; i++);

	return return_value;
}
