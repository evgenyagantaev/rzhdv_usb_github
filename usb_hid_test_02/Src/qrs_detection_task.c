/*
 * qrs_detection_task.c
 *
 *  Created on: Sep 8, 2016
 *      Author: root
 */

#include "qrs_obj.h"
#include "qrs_detection_task.h"
#include "gpio.h"

//debug
#include "usart.h"
extern UART_HandleTypeDef huart1;

void qrs_detection_task()
{
	if(qrs_get_new_sample_flag())
	{
		qrs_set_new_sample_flag(0);   // drop flag
		if(qrs_get_local_buffer_ready_flag())
			qrsDetect();

		//debug
		char message[64];  // remove when not debugging
		// debug
		/*
		sprintf(message, "%dI%d\r\n", qrs_window[0], isoline_window[0]);
		//sprintf(message, "%dI%d\r\n", qrs_window[0], qrs_window[0]);
		//sprintf(message, "%dI%d\r\n", isoline_window[0], isoline_window[0]);
		HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board
		if(markers[0] == WHITEMARKER)
			HAL_UART_Transmit(&huart1, "W\r\n", 3, 500);  // for production board
		else if(markers[0] == REDMARKER)
			HAL_UART_Transmit(&huart1, "R\r\n", 3, 500);  // for production board
		else if(markers[0] == BLUEMARKER)
			HAL_UART_Transmit(&huart1, "B\r\n", 3, 500);  // for production board
		//*/
		//debug


	}
}
