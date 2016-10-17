/*
 * qrs_detection_task.c
 *
 *  Created on: Sep 8, 2016
 *      Author: root
 */

#include "qrs_obj.h"
#include "qrs_detection_task.h"
#include "gpio.h"
#include "usbd_customhid_if.h"
#include "usbd_customhid.h"


//debug
#include "usart.h"
extern UART_HandleTypeDef huart1;
extern USBD_HandleTypeDef USBD_Device;

void qrs_detection_task()
{
	if(qrs_get_new_sample_flag())
	{
		qrs_set_new_sample_flag(0);   // drop flag
		if(qrs_get_local_buffer_ready_flag())
			qrsDetect();

		//debug
		char message[64];  // remove when not debugging
		message[0] = ADC_REPORT_ID;
		char marker_message[64];  // remove when not debugging
		marker_message[0] = ADC_REPORT_ID;
		// debug
		/*
		sprintf(message, "%dI%d\r\n", qrs_window[0], isoline_window[0]);
		//sprintf(message, "%dI%d\r\n", qrs_window[0] - isoline_window[0], 0);
		//sprintf(message, "%dI%d\r\n", isoline_window[0], isoline_window[0]);
		HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board
		/*
		if(markers[0] == WHITEMARKER)
			HAL_UART_Transmit(&huart1, "W\r\n", 3, 500);  // for production board
		else if(markers[0] == BLUEMARKER)
			HAL_UART_Transmit(&huart1, "B\r\n", 3, 500);  // for production board
		//*/
		/*
		if(markers[0] == REDMARKER)
			HAL_UART_Transmit(&huart1, "R\r\n", 3, 500);  // for production board

		//*/
		//debug
		if(qrs_detection_task_get_test_flag())
		{
			sprintf(&message[1], "%ldI%ld\r\n", qrs_window[0], isoline_window[0]);
			USBD_CUSTOM_HID_SendReport(&USBD_Device, (uint8_t *)message, strlen(message));

			//*
			if(markers[0] == REDMARKER)
			{
				HAL_Delay(2);
				sprintf(&marker_message[1], "R\r\n");
				USBD_CUSTOM_HID_SendReport(&USBD_Device, (uint8_t *)marker_message, strlen(marker_message));
			}
			//*/
		}





	}
}

int qrs_detection_task_get_test_flag()
{
	return test_flag;
}
void qrs_detection_task_set_test_flag()
{
	test_flag = 1;
}
void qrs_detection_task_drop_test_flag()
{
	test_flag = 0;
}
