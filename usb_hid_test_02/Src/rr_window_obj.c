/*
 * rr_window_obj.c
 *
 *  Created on: Aug 21, 2017
 *      Author: root
 */
#include "rr_window_obj.h"
#include "histogram_obj.h"


#include "usbd_customhid.h"
#include "usbd_customhid_if.h"
extern USBD_HandleTypeDef USBD_Device;

//debug
#include "usart.h"
extern UART_HandleTypeDef huart1;

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


}


void rr_window_sort_window(void)
{
	int i, j;
	int aux;

	//DEBUG
	//char message[64];  // remove when not debugging

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

	for(i=0;i<RR_WINDOW_LENGTH; i++)
	{
		//debug
		//sprintf(message, "%d  ", rr_window_sorted[i]);
		//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board
	}
	//sprintf(message, "\r\n*****\r\n");
	//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board
}

uint32_t rr_window_get_rr_window(int index)
{
	return rr_window[index];
}
uint32_t rr_window_get_sorted_rr_window(int index)
{
	return rr_window_sorted[index];
}

void rr_window_add_new_rr_interval(void)
{
	int i;
	//debug
	//*
	char message[64];  // remove when not debugging

	//*/

	if ((rr_window_new_rr_interval >= HISTOGRAM_LOW_BOUND) && (rr_window_new_rr_interval <= HISTOGRAM_UP_BOUND))
	{
		// 1. sdvinut' okno
		for(i=1; i<RR_WINDOW_LENGTH; i++)
		{
			rr_window[i-1] = rr_window[i];
		}
		// 2. dobavit' novyi interval
		rr_window[RR_WINDOW_LENGTH - 1] = rr_window_new_rr_interval;

		/*
		for(i=0;i<RR_WINDOW_LENGTH; i++)
		{
			//debug
			sprintf(message, "%d  ", rr_window[i]);
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board
		}
		sprintf(message, "\r\n*****\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board
		//*/
	}
}
