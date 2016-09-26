#include "gpio.h"
#include "spi_low_level.h"



uint32_t wait_for_drdy(void)
{
	while((drdy_adas_exti9_GPIO_Port->IDR & drdy_adas_exti9_Pin) != GPIO_PIN_RESET);
	//while(!new_frame_ready_flag);
	//new_frame_ready_flag = 0;

	return drdy_adas_exti9_GPIO_Port->IDR;
}

uint32_t chipsel_high(void)
{
	// set chipselect high (stop spi communication)
	HAL_GPIO_WritePin(GPIOA, spi1_chipsel_Pin, GPIO_PIN_SET);
	//GPIOA->BSRR = (uint32_t)spi1_chipsel_Pin;

	return GPIOA->ODR;
}

uint32_t chipsel_low(void)
{
	// set chipselect high (stop spi communication)
	HAL_GPIO_WritePin(GPIOA, spi1_chipsel_Pin, GPIO_PIN_RESET);
	//GPIOA->BRR = (uint32_t)spi1_chipsel_Pin;

	return GPIOA->ODR;
}

void synchronize(void)
{
	uint16_t in_data = 0x0000;

	wait_for_drdy();
	// set chipselect low (start spi communication)
	chipsel_low();

	//check if a receiver buffer is full (have not read any old data)
	if ((SPI1->SR & SPI_SR_RXNE) != RESET )
		in_data = SPI1->DR; // read

	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = (uint16_t)0xffff; // send
	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI1->DR; // read

	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = (uint16_t)0xffff; // send
	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI1->DR; // read

	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = (uint16_t)0xffff; // send
	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI1->DR; // read

	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = (uint16_t)0xffff; // send
	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI1->DR; // read
}

uint16_t write_2byte_word(uint16_t word16)
{
	long i;
	uint16_t in_data = 0x0000;
	uint16_t return_value;
	return_value = word16;

	wait_for_drdy();
	// set chipselect low (start spi communication)
	chipsel_low();

	//check if a receiver buffer is full (have not read any old data)
	if ((SPI1->SR & SPI_SR_RXNE) != RESET )
		in_data = SPI1->DR; // read
	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = word16; // send

	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI1->DR; // read

	// pause
	for(i=0; i<5; i++);
	// set chipselect high (stop spi communication)
	chipsel_high();
	//pause
	for(i=0; i<3; i++);

	return return_value;
}


uint16_t read_2byte_word(void)
{
	long i;
	uint16_t fictious_out_data = 0x0000;
	uint16_t return_value;

	wait_for_drdy();
	// set chipselect low (start spi communication)
	chipsel_low();

	//check if a receiver buffer is full (have not read any old data)
	if ((SPI1->SR & SPI_SR_RXNE) != RESET )
		return_value = SPI1->DR; // read
	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = fictious_out_data; // send

	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
	return_value = SPI1->DR; // read

	// pause
	for(i=0; i<5; i++);
	// set chipselect high (stop spi communication)
	chipsel_high();
	//pause
	for(i=0; i<3; i++);

	return return_value;
}


uint32_t write_4byte_word(uint32_t word32)
{
	long i;

	uint32_t local_copy = word32;
	uint32_t return_value = 0x00000000;

	uint16_t aux_16bit_word, aux1_16bit_word;

	wait_for_drdy();
	// set chipselect low (start spi communication)
	chipsel_low();

	aux_16bit_word = (uint16_t)(local_copy >> 16); // extract MS 16 bits

	//check if a receiver buffer is full (have not read any old data)
	if ((SPI1->SR & SPI_SR_RXNE) != RESET )
		return_value = SPI1->DR; // read
	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = aux_16bit_word; // send

	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
	aux1_16bit_word = SPI1->DR; // read

	return_value |= (uint32_t)(((uint32_t)aux_16bit_word) << 16); // for tests

	aux_16bit_word = (uint16_t)(local_copy); // extract LS 16 bits

	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = aux_16bit_word; // send

	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
	aux1_16bit_word = SPI1->DR; // read

	return_value |= (uint32_t)aux_16bit_word;

	// pause
	for(i=0; i<5; i++);
	// set chipselect high (stop spi communication)
	chipsel_high();
	//pause
	for(i=0; i<3; i++);

	return return_value;
}

uint32_t read_4byte_word(void)
{
	long i;

	uint16_t fictious_out_data = 0x0000;
	uint32_t return_value = 0x00000000;

	uint16_t aux_16bit_word;

	wait_for_drdy();
	// set chipselect low (start spi communication)
	chipsel_low();

	//check if a receiver buffer is full (have not read any old data)
	if ((SPI1->SR & SPI_SR_RXNE) != RESET )
		return_value = SPI1->DR; // read
	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = fictious_out_data; // send

	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
		aux_16bit_word = SPI1->DR; // read
	return_value |= (uint32_t)(((uint32_t)aux_16bit_word) << 16);

	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = fictious_out_data; // send

	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
		aux_16bit_word = SPI1->DR; // read
	return_value |= (uint32_t)aux_16bit_word;

	// pause
	for(i=0; i<5; i++);
	// set chipselect high (stop spi communication)
	chipsel_high();
	//pause
	for(i=0; i<3; i++);

	return return_value;
}

