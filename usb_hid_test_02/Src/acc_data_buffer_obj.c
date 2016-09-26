/*
 * acc_data_buffer_obj.c
 *
 *  Created on: Sep 12, 2016
 *      Author: root
 */

#include "acc_data_buffer_obj.h"

//debug
#include "usart.h"
extern UART_HandleTypeDef huart1;

// Method adds samples in buffers for analysis
void add_acc_samples(int16_t x, int16_t y, int16_t z)
{
	int i;

	// shift buffers
	for(i=0; i<(ACC_BUFFER_LENGTH-1); i++)
	{
		averaging_x_buffer[i] = averaging_x_buffer[i+1];
		averaging_y_buffer[i] = averaging_y_buffer[i+1];
		averaging_z_buffer[i] = averaging_z_buffer[i+1];
	}

	//add new samples
	averaging_x_buffer[ACC_BUFFER_LENGTH-1] = x;
	averaging_y_buffer[ACC_BUFFER_LENGTH-1] = y;
	averaging_z_buffer[ACC_BUFFER_LENGTH-1] = z;

	//debug
	//char message[64];  // remove when not debugging
	//sprintf(message, "%dI%d\r\n", averaging_x_buffer[ACC_BUFFER_LENGTH-1], averaging_x_buffer[ACC_BUFFER_LENGTH-1]);
	//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board

	//debug
	/*
	if((GPIOB->IDR & GPIO_PIN_0) == GPIO_PIN_RESET)
		GPIOB->BSRR = (uint32_t)GPIO_PIN_0;
	else
		GPIOB->BRR = (uint32_t)GPIO_PIN_0;
	//*/

	received_acc_counter++;
}

uint32_t acc_buffer_get_received_samples_counter()
{
	return received_acc_counter;
}



















