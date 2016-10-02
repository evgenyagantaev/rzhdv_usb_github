/*
 * leadoff_detection_task.c
 *
 *  Created on: Oct 2, 2016
 *      Author: root
 */

#include "leadoff_detection_task.h"
#include "leadoff_detector_obj.h"


void leadoff_detection_task()
{
	if(leadoff_detector_get_new_sample_flag())
	{
		leadoff_detector_drop_new_sample_flag();
		leadoff_detector_calculate_status();
	}
}
