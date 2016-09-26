#ifndef INC_TIMER250HZ_H_
#define INC_TIMER250HZ_H_

#include "tim.h"

// globals

TIM_HandleTypeDef htim3;
static uint32_t timer250hz_tick;

void timer250hz_start(void);
void timer250hz_increment_tick();
uint32_t timer250hz_get_tick();
void TIM3_IRQHandler(void);

#endif /* INC_TIMER250HZ_H_ */
