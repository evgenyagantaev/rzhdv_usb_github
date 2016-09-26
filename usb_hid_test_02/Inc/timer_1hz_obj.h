/*
 * timer_1000hz_obj.h
 *
 *  Created on: Sep 13, 2016
 *      Author: root
 */

#ifndef INC_TIMER_1HZ_OBJ_H_
#define INC_TIMER_1HZ_OBJ_H_

#include "tim.h"

TIM_HandleTypeDef htim1;

static uint32_t timer1hz_tick = 0;

void timer1hz_start(void);

void timer1hz_increment_tick();
uint32_t timer1hz_get_tick();


#endif /* INC_TIMER_1HZ_OBJ_H_ */
