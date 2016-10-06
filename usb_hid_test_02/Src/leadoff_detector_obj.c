/*
 * leadoff_detector_obj.c
 *
 *  Created on: Oct 2, 2016
 *      Author: root
 */

#include "leadoff_detector_obj.h"

//debug
#include "usart.h"
extern UART_HandleTypeDef huart1;


void leadoff_detector_push_new_sample(uint32_t new_sample, uint32_t ll_potential)
{
	leadoff_buffer_integral -= leadoff_detection_buffer[0];
	leadoff_buffer_integral += new_sample;
	leadoff_detector_shift_buffer();
	leadoff_detection_buffer[LEADOFF_DETECTION_BUFFER_LENGTH-1] = new_sample;
	leadoff_ll_potential = ll_potential;
	leadoff_detector_new_sample_flag = 1;
}

int leadoff_detector_get_new_sample_flag()
{
	return leadoff_detector_new_sample_flag;
}
void leadoff_detector_drop_new_sample_flag()
{
	leadoff_detector_new_sample_flag = 0;
}

uint32_t calculate_buffer_mean()
{
	return leadoff_buffer_integral / LEADOFF_DETECTION_BUFFER_LENGTH;
}
void leadoff_detector_calculate_status()
{
	buffer_mean_value = calculate_buffer_mean();

	if((buffer_mean_value < ABS_RANGE_LOW_BOUND) || (buffer_mean_value > ABS_RANGE_UP_BOUND))
		leadoff_status = 1; // lead off!!!
	else
	{
		uint32_t variation = calculate_variation();
		if(variation > VARIATION_UP_BOUND)
			leadoff_status = 1; // lead off!!!
		else
			leadoff_status = 0; // ok
	}
}
int leadoff_detector_get_status()
{
	return leadoff_status;
}

uint64_t calculate_variation()
{
	uint64_t return_value = 0;

	uint32_t current_min, current_max;
	int direction;

	if(leadoff_detection_buffer[1] < leadoff_detection_buffer[0])
	{
		current_max = leadoff_detection_buffer[0];
		current_min = leadoff_detection_buffer[1];
		direction = 0; // from max to min
	}
	else
	{
		current_max = leadoff_detection_buffer[1];
		current_min = leadoff_detection_buffer[0];
		direction = 1; // from min to max
	}

	int i = 0;
	for(i=3; i<LEADOFF_DETECTION_BUFFER_LENGTH; i++)
	{
		if(direction) // from min to max
		{
			if(leadoff_detection_buffer[i] < current_max) // local maximum detected
			{
				return_value += current_max - current_min;
				direction = 0; // now we will go from max to min
				current_min = leadoff_detection_buffer[i];
			}
			else // no local maximum yet
			{
				current_max = leadoff_detection_buffer[i];
			}

		}
		else //from max to min
		{
			if(leadoff_detection_buffer[i] > current_min) // local minimum detected
			{
				return_value += current_max - current_min;
				direction = 1; // now we will go from min to max
				current_max = leadoff_detection_buffer[i];
			}
			else // no local maximum yet
			{
				current_min = leadoff_detection_buffer[i];
			}

		}
	}


	// debug
	/*
	char message[64];  // remove when not debugging
	sprintf(message, "%LdI%Ld\r\n", return_value, return_value);
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board
	//*/

	return return_value;
}




void leadoff_detector_shift_buffer()
{
	int i;

	for(i=0; i<(LEADOFF_DETECTION_BUFFER_LENGTH-1); i++)
		leadoff_detection_buffer[i] = leadoff_detection_buffer[i+1];
}
