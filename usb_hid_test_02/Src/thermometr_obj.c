/*
 * thermometr_obj.c
 *
 *  Created on: Sep 20, 2016
 *      Author: root
 */

#include "thermometr_obj.h"
#include "gpio.h"


static uint32_t previous_temperature = 366;

uint32_t measure_temperature()
{

	// turn td power on
	//HAL_GPIO_WritePin(GPIOA, td_power_out_Pin, GPIO_PIN_SET);

	//HAL_ADC_Start(&hadc1);
	//if(HAL_ADC_PollForConversion(&hadc1, 1000) != HAL_OK)
	//{
		//Error_Handler();
	//}
	//uint32_t adc_ch0 = HAL_ADC_GetValue(&hadc1);
	// start conversions
	ADC1->CR |= ADC_CR_ADSTART;
	while((ADC1->ISR & ADC_FLAG_EOC) == 0);
	uint32_t adc_ch0 = ADC1->DR;
	double voltage = (double)adc_ch0 * 3300.0 / 4095.0;
	//HAL_ADC_Stop(&hadc1);

	// turn td power off
	//HAL_GPIO_WritePin(GPIOA, td_power_out_Pin, GPIO_PIN_RESET);
	voltage /= 0.909/0.96;
	double temperature = a*voltage*voltage + b*voltage + c;


	current_temperature = (uint32_t)(temperature * 10);
	// kalibrovka
	current_temperature -= 25;

	current_temperature = (current_temperature + previous_temperature) / 2;

	previous_temperature = current_temperature;

	return current_temperature;

}





uint32_t get_current_temperature()
{
	//debug
	//current_temperature = 210;

	return current_temperature;
}







