/*
 * recreation_curve_obj.c
 *
 *  Created on: Oct 4, 2016
 *      Author: root
 */

#include "recreation_curve_obj.h"
#include "diagnost_obj.h"
#include "timer_1hz_obj.h"


void recreation_curve_init()
{

	recreation_start_pulse = TACHYTHRESHOLD;
	recreation_start_time = 0;
}


void recreation_set_start_pule(int pulse)
{
	recreation_start_pulse = pulse;
}
int recreation_get_start_pulse()
{
	return recreation_start_pulse;
}

void recreation_set_start_time()
{
	recreation_start_time = timer1hz_get_tick();
}

int recreation_get_current_level()
{
	int return_value;
	int recreation_period = timer1hz_get_tick() - recreation_start_time;

	if(recreation_period < period1)
	{
		return_value = recreation_start_pulse - recreation_period * slope1;

	}
	else if((recreation_period >= period1) && (recreation_period < (period1 + period2)))
	{
		return_value = recreation_start_pulse - (period1 * slope1 + (recreation_period - period1)*slope2);
	}
	else
	{
		return_value = recreation_start_pulse - (period1 * slope1 + period2*slope2 + (recreation_period - (period1+period2))*slope3);
	}

	if(return_value < TACHYTHRESHOLD)
		return_value = TACHYTHRESHOLD;

	return return_value;
}


