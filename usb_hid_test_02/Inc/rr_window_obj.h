/*
 * rr_window_obj.h
 *
 *  Created on: Aug 21, 2017
 *      Author: root
 */

#ifndef RR_WINDOW_OBJ_H_
#define RR_WINDOW_OBJ_H_

#include "stdint.h"

static int new_rr_ready_flag;
static uint32_t new_rr_interval;

static uint32_t rr_window[128];

//------------------------------------

void rr_window_set_new_rr_ready_flag(int flag);
void rr_window_set_new_rr_interval(uint32_t interval);

uint32_t rr_window_get_rr_window(int index);
uint32_t rr_window_get_sorted_rr_window(int index);

void rr_window_add_new_rr_interval(uint32_t rr_interval);
void rr_window_sort_window(void);

#endif /* RR_WINDOW_OBJ_H_ */
