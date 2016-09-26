/*
 * timer_100hz_obj.c
 *
 *  Created on: Sep 12, 2016
 *      Author: root
 */

#include "timer_100hz_obj.h"
#include "tim.h"


void timer100hz_start(void)
{
    timer100hz_tick = 0;

    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /*Configure the TIM2 IRQ priority */
    HAL_NVIC_SetPriority(TIM2_IRQn, 2 ,0);

    /* Enable the TIM2 global Interrupt */
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    // enable update irq
    TIM2->DIER |= TIM_DIER_UIE;

    // prescaler value 79; counter frequency = 1MHz
    TIM2->PSC = (uint32_t)79;
    // auto reload value 10000; period = 10 mSec
    TIM2->ARR = (uint16_t)10000;

    // enable timer counter (start count)
    TIM2->CR1 |= TIM_CR1_CEN;
}

void timer100hz_increment_tick()
{
    timer100hz_tick++;

    //debug
	/*
	if((GPIOB->IDR & GPIO_PIN_0) == GPIO_PIN_RESET)
		GPIOB->BSRR = (uint32_t)GPIO_PIN_0;
	else
		GPIOB->BRR = (uint32_t)GPIO_PIN_0;
	//*/
}

uint32_t timer100hz_get_tick()
{
    return timer100hz_tick;
}
