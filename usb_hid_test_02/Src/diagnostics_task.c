/*
 * diagnosics_task.c
 *
 *  Created on: Sep 18, 2016
 *      Author: root
 */

#include "diagnostics_task.h"
#include "timer_1hz_obj.h"
#include "heart_rate_obj.h"
#include "thermometr_obj.h"

#include "usbd_hid.h"
extern USBD_HandleTypeDef USBD_Device;

//debug
#include "usart.h"
extern UART_HandleTypeDef huart1;

//debug
#include "gpio.h"
#include "leadoff_status_obj.h"


// This task performs diagnostics
void diagnosticsTask(void *parameters)
{

	char statusString[STATUSSTRINGLENGTH];

	// debug ***
	char timestamp[32];
	// debug ***

	static int local_call_stack_pointer;

	if(frozen_seconds_counter < timer1hz_get_tick())
	{
		//debug
		//HAL_GPIO_TogglePin(GPIOA, green_led_odrain_Pin);

		frozen_seconds_counter = timer1hz_get_tick();

		int current_heartrate = get_current_heartrate();

		if(current_heartrate != 444)
		{
			makeDiagnosis(current_heartrate,
			getWalkingStatus(), getRunningStatus(),
			getPosition());

			/*   integral'naya chss
			if(current_heartrate <= 85)
				common.heartRateWeight = 1;
			else
				common.heartRateWeight = (int)( 1.0 + 0.044*((double)(current_heartrate) - 85.0));

			// подсчитываем интегральную чсс
			long dI = (long)((double)current_heartrate * common.heartRateWeight);
				common.heartRateIntegral += dI;
			//*/
			// end integral'naya chss
		}


		// send status string via uart

		/*
		// adc fault (tyanetsya iz starogo)
		if(adcFault)
		{
			// no correct data from ADC
			sprintf(statusString, "c%dp%03dm%dt%03dr%03dG", 0,
				 777, motion, temperature, respiration);
		}
		else if(adcAbnormal)
		{
			adcAbnormal = 0;
			// no correct data from ADC
			sprintf(statusString, "c%dp%03dm%dt%03dr%03dG", 0,
				 555, motion, respiration);
		}
		else if(diagnost.badAdcRange)
		{

			if(diagnost.getBadAdcRangeFlag() == 0) // 444 appear right now
			{
				diagnost.setBadAdcRangeFlag();
				diagnost.setBadAdcRangeMarker(timer1hz_get_tick());

				sprintf(statusString, "c%dp%03dm%dt%03dr%03dG", diagnost.getStatus(),
				diagnost.getLastDisplayedPulse(), movementDetector.getPosition(),
				common.respirationCharge);
			}
			else // 444 appear in some moment in the past
			{
				if((timer1hz_get_tick() - getBadAdcRangeMarker()) > 10 ) // 444 more then 10 seconds
				{
					// adc input is out of range
					sprintf(statusString, "c%dp%03dm%dt%03dr%03dG", 0,
						   444, motion, respiration);
					common.heartRate = 444;

					//sprintf(debugstatus1, "Iso = %d\r\n", diagnost.badIsoline);
					//xSemaphoreTake(uartMutex, portMAX_DELAY);
					//uart.sendMessage(debugstatus1);
					//xSemaphoreGive(uartMutex);
					//vTaskDelay(delay10);
				}
				else // 444 less then 10 seconds
				{
					sprintf(statusString, "c%dp%03dm%dt%03dr%03dG", getStatus(),
					getLastDisplayedPulse(), getPosition(),
					respiration);
				}
			}


		}// end if(adcFault)
		//*/
		//else

		int motion = getPosition();
		int respiration = 17;
		int temperature = get_current_temperature();

		// current format of status string: "c%dp%03dm%dt%03dr%03dG"

		if(current_heartrate > 205)
		{
			// high noice in data
			if(getLastDisplayedPulse() == 444) // no normal pulse yet
			{
				sprintf(statusString, "c%dp%03dm%dt%03dr%03dG\r\n", 0, 444, motion, temperature, respiration);   // "c%dp%03dm%dt%03dr%03dG"

			}
			else
			{
				sprintf(statusString, "c%dp%03dm%dt%03dr%03dG\r\n", 0,333, motion, temperature, respiration);
			}
		}
		/*
		else if(isolineController.currentIsoline == 32768)    // no patient
		{
			sprintf(statusString, "c%dp%03dm%dt%03dr%03dG", 0,
					444, motion, temperature, respiration);
		}
		//*/
		else
		{
			// everything ok
			resetBadAdcRangeFlag();

			if(current_heartrate != 444)
			{

				//////////////////////////////////////////////////////////////////////////
				// DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG
				//make_hard_fault();
				// DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG



				setLastDisplayedPulse(current_heartrate);
				#ifndef WIDEDIAGNOSIS
				// print classic form of status string
				sprintf(statusString, "c%dp%03dm%dt%03dr%03dG\r\n", getStatus(), current_heartrate, getPosition(), temperature, respiration);
				#else
				// print form of status string with Bayevsky tension index and hr integral
				common.movement = movementDetector.getPosition();
				sprintf(statusString, "c%dp%03dm%dv%03db%03di%08ldG\r\n", diagnost.getStatus(),
				   common.heartRate, movementDetector.getPosition(),
				   temperature, respiration, (int)(rrHistogramm.getTensionIndex()), common.heartRateIntegral);


				#endif
			}
			else
			{
				sprintf(statusString, "c%dp%03dm%dt%03dr%03dG\r\n", 0,
				444, getPosition(),	temperature, respiration);
			}
			//sprintf(statusString, "c%dp%03dm%dv%03db%dG\r\n", diagnost.getStatus(),
			//common.heartRate, movementDetector.getPosition(),
			//respiration, (int)(rrHistogramm.getTensionIndex()));

			// debug recreation curve
			//sprintf(statusString, "c%dp%03dm%dt%03dr%03dG", diagnost.getStatus(),
			//ecgAnalizer.getHeartRate(), movementDetector.getPosition(),
			//diagnost.getTachiThreshold());
		}

		//output diagnosys
		long interval = getInterval();
		if((timer1hz_get_tick()%interval) == 0)
		{

			//if(common.sendStatus)
			{
				int i;
				//place report id in the beginning of message
				// shift string (terminating zero too)
				for(i=strlen(statusString); i>=0; i--)
				{
					statusString[i+1] = statusString[i];
				}
				statusString[0] = ADC_REPORT_ID;
				USBD_HID_SendReport(&USBD_Device, (uint8_t *)statusString, strlen(statusString));
				//HAL_UART_Transmit(&huart1, (uint8_t *)statusString, strlen(statusString), 500);  // for production board
				//debug
				//sprintf(statusString, "c  0x%x  G\r\n", get_leadoff_status());
				//HAL_UART_Transmit(&huart1, (uint8_t *)statusString, strlen(statusString), 500);  // for production board
			}
		}
	}// end if(frozen_seconds_counter < acc_buffer_get_received_samples_counter())

}










