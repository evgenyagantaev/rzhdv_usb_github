/*
 * isoline.h
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#ifndef INC_ISOLINE_H_
#define INC_ISOLINE_H_

#include "stdint.h"

#define ISOLINE_BUFFER_LENGTH 21
#define CUT_EDGES 5

static uint32_t current_isoline;

static uint32_t isoline_buffer[ISOLINE_BUFFER_LENGTH]; //
static uint32_t isoline_buffer_sorted[ISOLINE_BUFFER_LENGTH];

static int new_sample_added_flag;

void isoline_add_new_sample(uint32_t new_sample);
void calculate_isoline_value();
uint32_t get_isoline_value();
uint32_t get_last_sample();
int get_new_sample_flag();
void set_new_sample_flag(int flag);

// sluzhebnye funkcii
void shift_array(uint32_t *array, int LENGTH);
void copy_array(uint32_t *array_from, uint32_t *array_to, int LENGTH);
void sort(uint32_t *array, int LENGTH);

#endif /* INC_ISOLINE_H_ */
