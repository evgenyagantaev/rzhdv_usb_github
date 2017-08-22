/*
 * rr_window_task.c
 *
 *  Created on: Aug 21, 2017
 *      Author: root
 */
#include "rr_window_task.h"
#include "rr_window_obj.h"
#include "histogram_obj.h"

#include "usbd_customhid.h"
#include "usbd_customhid_if.h"
extern USBD_HandleTypeDef USBD_Device;


void rr_window_task(void)
{


	if(rr_window_get_new_rr_ready_flag())
	{
		//debug
		//*
		char message[64];  // remove when not debugging
		message[0] = ADC_REPORT_ID;
		sprintf(&message[1], "rr-window task\r\n");
		USBD_CUSTOM_HID_SendReport(&USBD_Device, (uint8_t *)message, strlen(message));
					//*/

		rr_window_get_rr_window(0);

		// dobavit, novyi rr-interval v okno
		rr_window_add_new_rr_interval();
		// 3. drop flag
		rr_window_set_new_rr_ready_flag(0);
		// otsortirovat' okno
		rr_window_sort_window();
		// vystavit' flag gotovnosti novogo okna
		histogram_new_window_ready_flag_set(1);
	}
}
