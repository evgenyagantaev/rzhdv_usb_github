/*
 * isoline_calculation_task.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#include <isoline.h>
#include "isoline_calculation_task.h"
#include "ecg_ring_buffer.h"
#include "qrs_obj.h"



void isoline_calculation_task()
{
	//debug
	char message[64];  // remove when not debugging

	if(get_new_sample_flag())  // new sample added, and isoline is not recalculated yet
	{
		calculate_isoline_value();
		set_new_sample_flag(0); // drop flag
		int32_t last_sample = get_last_sample();
		int32_t isoline_value = get_isoline_value();
		//int32_t ecg = last_sample - isoline_value;
		int32_t ecg = isoline_value;
		qrs_add_new_sample(last_sample);
		qrs_add_new_isoline(isoline_value);
		qrs_add_order_number(get_received_ecg_samples_counter());

	}
}










