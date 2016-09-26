/*
 * acc_data_buffer_obj.h
 *
 *  Created on: Sep 12, 2016
 *      Author: root
 */

#ifndef INC_ACC_DATA_BUFFER_OBJ_H_
#define INC_ACC_DATA_BUFFER_OBJ_H_

#define ACC_BUFFER_LENGTH 16

#include "stdint.h"

static uint32_t received_acc_counter = 0;

static int16_t averaging_x_buffer[ACC_BUFFER_LENGTH];
static int16_t averaging_y_buffer[ACC_BUFFER_LENGTH];
static int16_t averaging_z_buffer[ACC_BUFFER_LENGTH];

// Method adds samples in buffers for analysis
void add_acc_samples(int16_t x, int16_t y, int16_t z);

uint32_t acc_buffer_get_received_samples_counter();








#endif /* INC_ACC_DATA_BUFFER_OBJ_H_ */
