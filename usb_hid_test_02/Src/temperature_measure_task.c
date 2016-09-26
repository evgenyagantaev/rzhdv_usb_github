/*
 * temperature_measure_task.c
 *
 *  Created on: Sep 20, 2016
 *      Author: root
 */

#include "temperature_measure_task.h"
#include "thermometr_obj.h"


void temperature_measure_task()
{
	if(thermo_frozen_seconds_counter < timer1hz_get_tick())
	{
		thermo_frozen_seconds_counter = timer1hz_get_tick();
		measure_temperature();
	}
}








