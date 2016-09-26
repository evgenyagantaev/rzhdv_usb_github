/*
 * thermometr_obj.h
 *
 *  Created on: Sep 20, 2016
 *      Author: root
 */

#ifndef INC_THERMOMETR_OBJ_H_
#define INC_THERMOMETR_OBJ_H_

#include "adc.h"

static const double a = -7.858e-06;
static const double b = -1.778e-01;
static const double c = 2.0464e+02;


static uint32_t current_temperature;

extern ADC_HandleTypeDef hadc1;

uint32_t measure_temperature();
uint32_t get_current_temperature();

#endif /* INC_THERMOMETR_OBJ_H_ */
