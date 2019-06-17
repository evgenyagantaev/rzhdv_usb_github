/*
 * diagnosics_task.c
 *
 *  Created on: Sep 18, 2016
 *      Author: root
 */

#include "diagnostics_task.h"
#include "diagnost_obj.h"
#include "timer_1hz_obj.h"
#include "heart_rate_obj.h"
#include "thermometr_obj.h"
#include "leadoff_detector_obj.h"
#include "movement_detector_obj.h"
#include "histogram_obj.h"

#include "usbd_customhid.h"
#include "usbd_customhid_if.h"
extern USBD_HandleTypeDef USBD_Device;

//debug
#include "usart.h"
extern UART_HandleTypeDef huart1;

//debug
#include "gpio.h"


// This task performs diagnostics
void diagnosticsTask(void *parameters)
{


	char statusString[STATUSSTRINGLENGTH];


	if(frozen_seconds_counter < timer1hz_get_tick())
	{
		frozen_seconds_counter = timer1hz_get_tick();

		int motion = getPosition();
		int respiration = 17;
		int temperature = get_current_temperature();

		if(leadoff_detector_get_status())
		{
			sprintf(statusString, "c%dp%03dm%dt%03dr%03db%03di%08ldG\r\n", 0, 333, motion,	temperature, respiration, 0, 0);
		}
		else
		{

			int current_heartrate = get_current_heartrate();

			if(current_heartrate > 205)
			{
				// high noice in data
				if(getLastDisplayedPulse() == 444) // no normal pulse yet
				{
					sprintf(statusString, "c%dp%03dm%dt%03dr%03db%03di%08ldG\r\n", 0, 444, motion, temperature, respiration, 0, 0);   // "c%dp%03dm%dt%03dr%03dG"

				}
				else
				{
					sprintf(statusString, "c%dp%03dm%dt%03dr%03db%03di%08ldG\r\n", 0,333, motion, temperature, respiration, 0, 0);
				}
			}
			else // current heartrate <= 205
			{
				setLastDisplayedPulse(current_heartrate);

				makeDiagnosis(current_heartrate, getWalkingStatus(), getRunningStatus(), getPosition());

				//*
				//integral'naya chss
				if(current_heartrate <= 85)
					heart_rate_weight = 1;
				else
					heart_rate_weight = (int)( 1.0 + 0.044*((double)(current_heartrate) - 85.0));

				// подсчитываем интегральную чсс
				long dI = (long)((double)current_heartrate * heart_rate_weight);
					heart_rate_integral += dI;
				//*/
				// end integral'naya chss

#define WIDEDIAGNOSIS

				#ifndef WIDEDIAGNOSIS
				// print classic form of status string
				sprintf(statusString, "c%dp%03dm%dt%03dr%03dG\r\n", getStatus(), current_heartrate, motion, temperature, respiration);
				#else
				// print form of status string with Bayevsky tension index and hr integral
				sprintf(statusString, "c%dp%03dm%dt%03dr%03db%03di%08ldG\r\n", getStatus(),current_heartrate, motion,temperature, respiration, histogram_get_tension_index(), heart_rate_integral);


				#endif
			}
		}

		//output diagnosys
		long interval = getInterval();
		if((timer1hz_get_tick()%interval) == 0)
		{
			int i;
			//place report id in the beginning of message
			// shift string (terminating zero too)
			for(i=strlen(statusString); i>=0; i--)
			{
				statusString[i+1] = statusString[i];
			}
			statusString[0] = ADC_REPORT_ID;
			USBD_CUSTOM_HID_SendReport(&USBD_Device, (uint8_t *)statusString, strlen(statusString));

			HAL_UART_Transmit(&huart1, (uint8_t *)statusString, strlen(statusString), 500);  // for production board
			//debug
			//sprintf(statusString, "c  0x%x  G\r\n", get_leadoff_status());
			//HAL_UART_Transmit(&huart1, (uint8_t *)statusString, strlen(statusString), 500);  // for production board

		}
	}// end if(frozen_seconds_counter < acc_buffer_get_received_samples_counter())

}










