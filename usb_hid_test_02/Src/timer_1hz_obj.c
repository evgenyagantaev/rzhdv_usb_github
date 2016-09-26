/*
 * timer_1000hz_obj.c
 *
 *  Created on: Sep 13, 2016
 *      Author: root
 */

#include <timer_1hz_obj.h>
#include "tim.h"

//debug
#include "gpio.h"


void timer1hz_start(void)
{
    timer1hz_tick = 0;

    /* Peripheral clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();

    /*Configure the TIM4 IRQ priority */
    HAL_NVIC_SetPriority(TIM4_IRQn, 2 ,0);

    /* Enable the TIM4 global Interrupt */
    HAL_NVIC_EnableIRQ(TIM4_IRQn);

    // enable update irq
    TIM4->DIER |= TIM_DIER_UIE;

    // prescaler value 79; counter frequency = 1MHz
    TIM4->PSC = (uint32_t)19999; // 1KHz
    // auto reload value 10000; period = 1 Sec
    TIM4->ARR = (uint16_t)4000;

    // enable timer counter (start count)
    TIM4->CR1 |= TIM_CR1_CEN;
}

void timer1hz_increment_tick()
{
    timer1hz_tick++;
    //HAL_GPIO_TogglePin(GPIOA, green_led_odrain_Pin);

    //debug
	/*
	if((GPIOB->IDR & GPIO_PIN_0) == GPIO_PIN_RESET)
		GPIOB->BSRR = (uint32_t)GPIO_PIN_0;
	else
		GPIOB->BRR = (uint32_t)GPIO_PIN_0;
	//*/

}

uint32_t timer1hz_get_tick()
{
    return timer1hz_tick;
}
























