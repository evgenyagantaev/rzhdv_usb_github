/*
 * histogram_obj.c
 *
 *  Created on: Aug 21, 2017
 *      Author: root
 */
#include "histogram_obj.h"
#include "rr_window_obj.h"
#include "heart_rate_obj.h"

#include "usbd_customhid_if.h"
#include "usbd_customhid.h"


//debug
#include "usart.h"
extern UART_HandleTypeDef huart1;
extern USBD_HandleTypeDef USBD_Device;


void histogram_new_window_ready_flag_set(int flag)
{
	histogram_new_window_ready_flag = flag;
}
int histogram_new_window_ready_flag_get(void)
{
	return histogram_new_window_ready_flag;
}
void histogram_drop_new_window_ready_flag()
{
	histogram_new_window_ready_flag = 0;
}

void histogram_clean() // obnulyaem massiv gistogrammy
{
	int i;

	for(i=0; i<NUMBER_OF_BINS; i++)
	{
		histogram[i] = 0;
	}
}


void histogram_fill() //zapolnyaem massiv gistogrammy
{
	int i=0, j=0;

	int lb = 0;
	int ub = HISTOGRAM_LOW_BOUND;

	while((i<NUMBER_OF_BINS) && (j<RR_WINDOW_LENGTH))
	{
		if((rr_window_get_sorted_rr_window(j) > lb) && (rr_window_get_sorted_rr_window(j) <= ub))
		{
			histogram[i]++;
			j++; // one step on sorted array
		}
		else
		{
			lb = HISTOGRAM_LOW_BOUND + BIN_STEP * i;
			ub = lb + BIN_STEP;
			i++; // one step on histogramm array

		}
	}
}


void histogram_tension_index_calculate() // calculate tension
{
	//debug
	/*
	char message[64];  // remove when not debugging
	message[0] = ADC_REPORT_ID;
	sprintf(&message[1], "tension calculation subroutine\r\n");
	USBD_CUSTOM_HID_SendReport(&USBD_Device, (uint8_t *)message, strlen(message));
	//*/

	double min = rr_window_get_sorted_rr_window(0);
	double max = rr_window_get_sorted_rr_window(RR_WINDOW_LENGTH-1);
	double moda = HISTOGRAM_LOW_BOUND;
	double moda_amplitude = 0;

	int i;
	for(i=0; i<NUMBER_OF_BINS; i++)
	{
		if(histogram[i] > moda_amplitude)
		{
			moda_amplitude = histogram[i];
			moda = HISTOGRAM_LOW_BOUND + BIN_STEP*i;
		}
	}

	int current_heartrate = get_current_heartrate();
	tension_index = rr_window_get_rr_window(RR_WINDOW_LENGTH-1);
	//debug
		//*
		char message[64];  // remove when not debugging
		message[0] = ADC_REPORT_ID;
		sprintf(&message[1], "tension index %d\r\n", tension_index);
		USBD_CUSTOM_HID_SendReport(&USBD_Device, (uint8_t *)message, strlen(message));
		//*/

	if((current_heartrate >= 45) && (current_heartrate <= 110) && ((double)(max - min))/((double)max) < 0.3)
	{
		moda_amplitude = moda_amplitude * 100.0 / RR_WINDOW_LENGTH;
		moda = moda / 1000.0;
		tension_index = rr_window_get_rr_window(RR_WINDOW_LENGTH-1);
		/*
		if(((max - min) > 0) && (min > 200))
			//tension_index = moda_amplitude / (2 * moda * ((max - min)/1000.0));
		else
			tension_index = 0;
		//*/
	}
	else
		tension_index = 0;


}

int histogram_get_tension_index(void)
{
	return (int)tension_index;
}
