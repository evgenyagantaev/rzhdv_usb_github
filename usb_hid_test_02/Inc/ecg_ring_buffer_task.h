/*
 * ecg_ring_buffer_task.h
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#ifndef INC_ECG_RING_BUFFER_TASK_H_
#define INC_ECG_RING_BUFFER_TASK_H_
#include "stdint.h"

#define ADAS_FRAME_LENGTH 13

static uint32_t local_frame_copy[ADAS_FRAME_LENGTH];

void ecg_ring_buffer_task();

#endif /* INC_ECG_RING_BUFFER_TASK_H_ */
