/*
 * smb380.c
 *
 *  Created on: Sep 2, 2016
 *      Author: root
 */

#include "smb380.h"
#include "acc_spi_low_level.h"
#include "gpio.h"


void smb380_write_settings() //write smb380 accelerometer settings
{
	uint8_t tmp;


	acc_spi_write_2byte_word(0x1580);      //write settings at 0x15 register, bit 7 for SPI4
								  	  	   //bit 3 for not blocking MSB, bit 4 for int latch

	tmp = acc_spi_read_1byte(0x14);      //read calibration data from 0x14 register
	tmp=(tmp&0xe0)+0x0e;                 //save calibration data and write range (4g) and bandwidth(1500Hz)
	acc_spi_write_2byte_word((((uint16_t)0x14)<<8) + tmp);

	acc_spi_write_2byte_word(((uint16_t)0x0b)<<8);    //write int settings at 0x0b register
}


void smb380_read_xyz_rawdata(uint8_t *data) //read smb380 xyz h and l registers to buffer
{
	uint8_t aux = 0;
	uint16_t in_data, out_data;

	acc_spi_chipsel_low();

	//check if a receiver buffer is full (have not read any old data)
	if ((SPI2->SR & SPI_SR_RXNE) != RESET )
		in_data = SPI2->DR; // read

	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	out_data = (((uint16_t)0x02)<<8)|0x8000; //0x02 register with first RW bit for read mode
	SPI2->DR = out_data; // send

	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI2->DR; // read

	data[0] = (uint8_t)in_data;

	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = 0xffff; // send dummy data
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI2->DR; // read

	data[1] = (uint8_t)(in_data>>8);   // msb
	data[2] = (uint8_t)in_data;        // lsb

	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = 0xffff; // send dummy data
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI2->DR; // read

	data[3] = (uint8_t)(in_data>>8);   // msb
	data[4] = (uint8_t)in_data;        // lsb

	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = 0xffff; // send dummy data
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI2->DR; // read

	data[5] = (uint8_t)(in_data>>8);   // msb
	data[6] = (uint8_t)in_data;        // lsb      temperature

	acc_spi_chipsel_high();

}
