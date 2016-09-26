/*
 * timer_100hz_obj.h
 *
 *  Created on: Sep 12, 2016
 *      Author: root
 */

#ifndef INC_TIMER_100HZ_OBJ_H_
#define INC_TIMER_100HZ_OBJ_H_
#include "tim.h"

TIM_HandleTypeDef htim2;

static uint32_t timer100hz_tick = 0;

void timer100hz_start(void);

void timer100hz_increment_tick();
uint32_t timer100hz_get_tick();

#endif /* INC_TIMER_100HZ_OBJ_H_ */
