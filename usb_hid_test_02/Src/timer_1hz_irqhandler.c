/*
 * timer_1hz_irqhandler.c
 *
 *  Created on: Sep 13, 2016
 *      Author: root
 */

#include "timer_1hz_obj.h"



void TIM4_IRQHandler(void)
{
    if((TIM4->SR & TIM_SR_UIF) != 0) // update interrupt pending flag
    {
        // clear flag
        TIM4->SR &= ~TIM_SR_UIF;

        timer1hz_increment_tick();
    }
}

