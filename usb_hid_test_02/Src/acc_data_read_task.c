/*
 * acc_data_read_task.c
 *
 *  Created on: Sep 2, 2016
 *      Author: root
 */

#include "acc_data_read_task.h"
#include "smb380.h"
#include "stdint.h"
#include "acc_data_buffer_obj.h"
#include "movement_detector_obj.h"


//debug
#include "acc_spi_low_level.h"

void acc_data_read_task()
{
	//debug
	uint8_t accelerometer_data[16];
	int16_t rawX=0, rawY=0, rawZ=0;
	int16_t rawT=0;
	uint8_t lsb;

	if(acc_buffer_get_received_samples_counter() < timer100hz_get_tick())
	{

		smb380_read_xyz_rawdata(accelerometer_data);

		rawX = accelerometer_data[1]; rawX <<= 8; lsb = accelerometer_data[0] & 0xC0;
		rawX += lsb;
		rawX /= 64;     // >> 6

		rawY = accelerometer_data[3]; rawY <<= 8; lsb = accelerometer_data[2] & 0xC0;
		rawY += lsb;
		rawY /= 64;     // >> 6

		rawZ = accelerometer_data[5]; rawZ <<= 8; lsb = accelerometer_data[4] & 0xC0;
		rawZ += lsb;
		rawZ /= 64;     // >> 6

		rawT=accelerometer_data[6];
		rawT=(rawT>>1) - 30;

		lsb =0;

		add_acc_samples(rawX, rawY, rawZ);
		addAccSamples(rawX, rawY, rawZ);

	}
}





