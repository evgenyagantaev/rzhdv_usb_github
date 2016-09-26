/*
 * heart_rate_calculation_task.c
 *
 *  Created on: Sep 10, 2016
 *      Author: root
 */


#include "heart_rate_calculation_task.h"
#include "qrs_obj.h"

//debug
#include "usart.h"
extern UART_HandleTypeDef huart1;


void heart_rate_calculation_task()
{
	if(get_new_rr_interval_flag())
	{
		//drop flag
		set_new_rr_interval_flag(0);

		uint32_t new_rr_interval = qrs_get_new_rr_interval();
		hr_set_new_rr_interval(new_rr_interval);
		heart_rate_calculate();
		//*
		// debug
		if(new_rr_interval != 0)
		{
			//debug
			/*
			char message[64];  // remove when not debugging
			sprintf(message, "c1p%03dm5t366r0014G\r\n", get_current_heartrate());
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board
			//*/
		}
		//*/
	}
}






















