/*
 * leadoff_detector_obj.h
 *
 *  Created on: Oct 2, 2016
 *      Author: root
 */

#ifndef LEADOFF_DETECTOR_OBJ_H_
#define LEADOFF_DETECTOR_OBJ_H_

#include "stdint.h"

#define LEADOFF_DETECTION_BUFFER_LENGTH 256

static const uint32_t ABS_RANGE_LOW_BOUND = 7000000;
static const uint32_t ABS_RANGE_UP_BOUND = 11500000;
static const uint32_t VARIATION_UP_BOUND = 700000;
static const uint32_t LLTHRESHOLD = 10000000;


static uint32_t leadoff_detection_buffer[LEADOFF_DETECTION_BUFFER_LENGTH];
static int leadoff_detector_new_sample_flag = 0;
static uint64_t leadoff_buffer_integral = 0x7fffff; // 23 разряда 111 1111  1111 1111  1111 1111
static uint32_t buffer_mean_value = 0;
static int leadoff_status = 0;  // 0 - ok, 1 - lead off

static uint32_t variation;

void leadoff_detector_push_new_sample(uint32_t new_sample, uint32_t ll_potential);

int leadoff_detector_get_new_sample_flag();
void leadoff_detector_drop_new_sample_flag();

uint32_t calculate_buffer_mean();
void leadoff_detector_calculate_status();
int leadoff_detector_get_status();

uint64_t calculate_variation();

static uint32_t leadoff_ll_potential;


void leadoff_detector_shift_buffer();

#endif /* LEADOFF_DETECTOR_OBJ_H_ */
