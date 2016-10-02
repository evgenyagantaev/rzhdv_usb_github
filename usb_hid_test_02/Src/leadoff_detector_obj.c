/*
 * leadoff_detector_obj.c
 *
 *  Created on: Oct 2, 2016
 *      Author: root
 */

#include "leadoff_detector_obj.h"


void leadoff_detector_push_new_sample(uint32_t new_sample)
{
	leadoff_buffer_integral -= leadoff_detection_buffer[0];
	leadoff_buffer_integral += new_sample;
	leadoff_detector_shift_buffer();
	leadoff_detection_buffer[LEADOFF_DETECTION_BUFFER_LENGTH-1] = new_sample;
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
		leadoff_status = 0; // ok
}
int leadoff_detector_get_status()
{
	return leadoff_status;
}

uint32_t calculate_variation()
{
	uint32_t return_value = 0;

	uint32_t current_min = leadoff_detection_buffer[0];
	int i = 0;
}




void leadoff_detector_shift_buffer()
{
	int i;

	for(i=0; i<(LEADOFF_DETECTION_BUFFER_LENGTH-1); i++)
		leadoff_detection_buffer[i] = leadoff_detection_buffer[i+1];
}
