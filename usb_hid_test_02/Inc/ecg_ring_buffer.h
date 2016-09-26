#ifndef INC_ECG_RING_BUFFER_H_
#define INC_ECG_RING_BUFFER_H_

#include "stdint.h"

#define ECGBUFFERLENGTH 64

// locals
static uint32_t received_ecg_samples_counter;

static uint32_t ecg_ring_buffer[ECGBUFFERLENGTH];
static uint32_t current_ecg_push_index;
static uint32_t current_ecg_pop_index;

int ecg_overflow_flag;

// возвращает 0
int ecg_ring_buffer_initialization(void);

//
int ecg_ring_buffer_push(uint32_t sample);
int ecg_ring_buffer_pop(uint32_t *sample);
uint32_t get_received_ecg_samples_counter();

#endif /* INC_ECG_RING_BUFFER_H_ */
