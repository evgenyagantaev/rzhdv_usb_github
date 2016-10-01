/*
 * ecg_ring_buffer_task.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#include "ecg_ring_buffer_task.h"
#include "ecg_ring_buffer.h"
#include "frame_ring_buffer.h"
#include "isoline.h"

//debug
#include "usart.h"
extern UART_HandleTypeDef huart1;


void ecg_ring_buffer_task()
{
	char message[64];

	if(get_received_ecg_samples_counter() < get_received_frames_counter())
	{
		frame_ring_buffer_pop(local_frame_copy, ADAS_FRAME_LENGTH);
		uint32_t sample = local_frame_copy[1]&((uint32_t)0x00ffffff);
		ecg_ring_buffer_push(sample);
		isoline_add_new_sample(sample);
		// save leadoff status (9-th word if frame, address 0x1d)
		if((uint8_t)(local_frame_copy[9]>>24) == 0x1d)
		{
			set_leadoff_status((uint8_t)((local_frame_copy[9]>>16) & 0x000000ff));
		}

		// debug
		//char message[64];  // remove when not debugging
		//sprintf(message, "%dI%d\r\n", sample, sample);
		//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board

	}
}
