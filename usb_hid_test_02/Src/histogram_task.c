/*
 * histogram_task.c
 *
 *  Created on: Aug 21, 2017
 *      Author: root
 */
#include "histogram_task.h"
#include "histogram_obj.h"

#include "usbd_customhid.h"
#include "usbd_customhid_if.h"
extern USBD_HandleTypeDef USBD_Device;

void histogram_task(void)
{


	if(histogram_new_window_ready_flag_get())
	{
		// drop flag
		histogram_drop_new_window_ready_flag();
		// ochistit' gistogrammu
		histogram_clean();
		// zapolnit' gistogrammu
		histogram_fill();
		// calculate tension index
		histogram_tension_index_calculate();
	}
}
