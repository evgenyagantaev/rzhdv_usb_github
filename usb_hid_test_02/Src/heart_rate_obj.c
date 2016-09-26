/*
 * heart_rate_obj.c
 *
 *  Created on: Sep 10, 2016
 *      Author: root
 */

#include "heart_rate_obj.h"




void heart_rate_init()
{
	int i;

	for(i=0; i<BUFFER_LENGTH; i++)
		regular_heart_rate_buffer[i] = 75;
}


int get_current_heartrate()
{
	if(current_heartrate == 0)
		return current_heartrate;
	else
		return current_heartrate + 1;
}

void heart_rate_set_asystoly()
{
	current_heartrate = 0;
}

void hr_set_new_rr_interval(uint32_t interval)
{
	new_rr_interval = interval;
}


//---------------------------------------------------------------------------
// Method calculates rr-interval and heart rate and manipulates with
// heart rate buffers
void heart_rate_calculate(void)
{

  // calculate heartRate
	new_heart_rate = 60000 / new_rr_interval;

  // look up what about to insert this heart rate in regular buffer
  if((abs(new_heart_rate - regular_average)*100/regular_average) < MAXHEARTRATEDEVIATION)
  {
	 //shift regular and quarantine buffers
	 for(int i=0; i<(REGULARANDQUARANTINEBUFFERLENGTH - 1); i++)
	 {
		 regular_heart_rate_buffer[i] = regular_heart_rate_buffer[i+1];
		 quarantine_heart_rate_buffer[i] = quarantine_heart_rate_buffer[i+1];
	 }
	 // add value in regular and quarantine buffers
	 regular_heart_rate_buffer[REGULARANDQUARANTINEBUFFERLENGTH - 1] = new_heart_rate;
	 quarantine_heart_rate_buffer[REGULARANDQUARANTINEBUFFERLENGTH - 1] = new_heart_rate;

	 // set flag for rr interval collection procedure
	 new_regular_heart_rate_ready_flag = 1;


	 // calculate average of regular buffer
	 regular_average = hr_calculate_average(regular_heart_rate_buffer, REGULARANDQUARANTINEBUFFERLENGTH);
	 if(current_heartrate == 444) // there was not real pulse yet
	 {
		if((regular_average < 130) && (regular_average > 40)) // if normal start pulse
			current_heartrate = regular_average;
	 }
	 else
		 current_heartrate = regular_average;

	 // calculate average of quarantine buffer
	 quarantine_average = hr_calculate_average(quarantine_heart_rate_buffer, REGULARANDQUARANTINEBUFFERLENGTH);
  }//end if((abs(heartRate - regularAverage)*100/regularAverage) < MAXHEARTRATEDEVIATION)
  else // here is an excess of permissible deviation from average
  {
	 // so we add value in quarantine buffer *******************************

	 // shift quarantine buffer
	 for(int i=0; i<(REGULARANDQUARANTINEBUFFERLENGTH - 1); i++)
	 {
		 quarantine_heart_rate_buffer[i] = quarantine_heart_rate_buffer[i+1];
	 }
	 // add value
	 quarantine_heart_rate_buffer[REGULARANDQUARANTINEBUFFERLENGTH - 1] = new_heart_rate;
	 // calculate average of quarantine buffer
	 quarantine_average = hr_calculate_average(quarantine_heart_rate_buffer, REGULARANDQUARANTINEBUFFERLENGTH);

	 // check if we have to open quarantine ********************************

	 // check the deviation of quarantine buffer content from a quarantine mean
	 int deviationOk = 1;
	 int i = 0;
	 while (deviationOk && (i < REGULARANDQUARANTINEBUFFERLENGTH))
	 {
		if (abs((quarantine_heart_rate_buffer[i] - quarantine_average) * 100 / quarantine_average) > MAXHEARTRATEDEVIATION)
			   deviationOk = 0;
		else
			   i++;
	 }

	 // if deviation ok, open quarantine (copy quarantine buffer in
	 // regular buffer)
	 if (deviationOk)
	 {
		for (int i = 0; i < REGULARANDQUARANTINEBUFFERLENGTH; i++)
			regular_heart_rate_buffer[i] = quarantine_heart_rate_buffer[i];
		regular_average = quarantine_average;
	 }
  }// end else


}// end heartRateCalculate
//--------------------------end----------------------------------------------


uint32_t hr_calculate_average(uint32_t *array, int LENGTH)
{
	uint32_t return_value = 0;
	int i;

	for(i=0; i<LENGTH; i++)
		return_value += array[i];
	return_value /= LENGTH;

	return return_value;
}










