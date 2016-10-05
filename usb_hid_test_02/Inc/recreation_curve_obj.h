/*
 * recreation_curve_obj.h
 *
 *  Created on: Oct 4, 2016
 *      Author: root
 */

#ifndef RECREATION_CURVE_OBJ_H_
#define RECREATION_CURVE_OBJ_H_

#include "stdint.h"

static const int slope1 = 0.3;
static const int slope2 = 0.25;
static const int slope3 = 0.15;

static const int period1 = 60;
static const int period2 = 120;


static int recreation_start_pulse;
static uint32_t recreation_start_time;



void recreation_curve_init();

void recreation_set_start_pule(int pulse);
int recreation_get_start_pulse();

void recreation_set_start_time();

int recreation_get_current_level();

#endif /* RECREATION_CURVE_OBJ_H_ */
