/*
 * rr_window_obj.c
 *
 *  Created on: Aug 21, 2017
 *      Author: root
 */
#include "rr_window_obj.h"


#include "usbd_customhid.h"
#include "usbd_customhid_if.h"
extern USBD_HandleTypeDef USBD_Device;

void rr_window_set_new_rr_ready_flag(int flag)
{
	new_rr_ready_flag = flag;
}

int rr_window_get_new_rr_ready_flag(void)
{
	return new_rr_ready_flag;
}


void rr_window_set_new_rr_interval(uint32_t interval)
{
	rr_window_new_rr_interval = interval;

	//debug
	//*
	char message[64];  // remove when not debugging
	message[0] = ADC_REPORT_ID;
	sprintf(&message[1], "rr-window set rr interval %d\r\n", rr_window_new_rr_interval);
	USBD_CUSTOM_HID_SendReport(&USBD_Device, (uint8_t *)message, strlen(message));
	//*/
}


void rr_window_sort_window(void)
{
	int i, j;
	int aux;

	// copy window into the sorted window
	for(i=0; i<RR_WINDOW_LENGTH; i++)
	{
		rr_window_sorted[i] = rr_window[i];
	}

	// sort sorted window (bubble sort; ascending)
	for(i=0; i<(RR_WINDOW_LENGTH-1); i++)
	{
		for(j=(RR_WINDOW_LENGTH-1); j>i; j--)
		{
			if(rr_window_sorted[j] < rr_window_sorted[j-1])
			{
				aux = rr_window_sorted[j];
				rr_window_sorted[j] = rr_window_sorted[j-1];
				rr_window_sorted[j-1] = aux;
			}
		}
	}
}

uint32_t rr_window_get_rr_window(int index)
{


	//debug
	//*
	char message[64];  // remove when not debugging
	message[0] = ADC_REPORT_ID;
	sprintf(&message[1], "rr-window get rr window %d   %d\r\n", rr_window[index], index);
	USBD_CUSTOM_HID_SendReport(&USBD_Device, (uint8_t *)message, strlen(message));
	//*/

	return rr_window[index];
}
uint32_t rr_window_get_sorted_rr_window(int index)
{
	return rr_window_sorted[index];
}

void rr_window_add_new_rr_interval(void)
{
	int i;

	// 1. sdvinut' okno
	for(i=1; i<RR_WINDOW_LENGTH; i++)
	{
		rr_window[i-1] = rr_window[i];
	}
	// 2. dobavit' novyi interval
	rr_window[RR_WINDOW_LENGTH - 1] = rr_window_new_rr_interval;


}
