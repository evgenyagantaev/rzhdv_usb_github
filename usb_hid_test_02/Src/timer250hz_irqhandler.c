#include "timer250hz.h"


void TIM3_IRQHandler(void)
{
    if((TIM3->SR & TIM_SR_UIF) != 0) // update interrupt pending flag
    {
        // clear flag
        TIM3->SR &= ~TIM_SR_UIF;

        timer250hz_increment_tick();
        //debug
        //*
        if((GPIOB->IDR & GPIO_PIN_0) == GPIO_PIN_RESET)
        	GPIOB->BSRR = (uint32_t)GPIO_PIN_0;
        else
        	GPIOB->BRR = (uint32_t)GPIO_PIN_0;
        //*/
    }
}
