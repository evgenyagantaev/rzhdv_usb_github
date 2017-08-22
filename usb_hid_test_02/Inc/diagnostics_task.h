/*
 * diagnosics_task.h
 *
 *  Created on: Sep 18, 2016
 *      Author: root
 */

#ifndef INC_DIAGNOSTICS_TASK_H_
#define INC_DIAGNOSTICS_TASK_H_

#include "stdint.h"

# define STATUSSTRINGLENGTH 128


static uint32_t frozen_seconds_counter = 0;
static long heart_rate_integral;
static int heart_rate_weight;

#endif /* INC_DIAGNOSTICS_TASK_H_ */
