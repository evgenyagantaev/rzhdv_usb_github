/*
 * rr_window_obj.h
 *
 *  Created on: Aug 21, 2017
 *      Author: root
 */

#ifndef RR_WINDOW_OBJ_H_
#define RR_WINDOW_OBJ_H_

#define RR_WINDOW_LENGTH 128

#include "stdint.h"

static int new_rr_ready_flag;
static uint32_t rr_window_new_rr_interval;

static uint32_t rr_window[RR_WINDOW_LENGTH];
static uint32_t rr_window_sorted[RR_WINDOW_LENGTH];

//------------------------------------

void rr_window_set_new_rr_ready_flag(int flag);
int rr_window_get_new_rr_ready_flag(void);
void rr_window_set_new_rr_interval(uint32_t interval);

uint32_t rr_window_get_rr_window(int index);
uint32_t rr_window_get_sorted_rr_window(int index);

void rr_window_add_new_rr_interval(void);
void rr_window_sort_window(void);

#endif /* RR_WINDOW_OBJ_H_ */
