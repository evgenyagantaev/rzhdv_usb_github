#ifndef INC_FRAME_RING_BUFFER_H_
#define INC_FRAME_RING_BUFFER_H

#include "stdint.h"

#define RAWS 16
#define COLUMNS 13


// locals
static uint32_t received_frames_counter;

uint32_t frame_ring_buffer[RAWS][COLUMNS];
uint32_t primary_buffer[COLUMNS];
uint32_t secondary_buffer[COLUMNS];
uint32_t current_push_index;
uint32_t current_pop_index;

int overflow_flag;


// returns summ of initialized (with 0) values
int frame_ring_buffer_initialization(void);
// returns
int frame_ring_buffer_push(uint32_t *frame, int length);
int frame_ring_buffer_pop(uint32_t *frame, int length);
uint32_t get_received_frames_counter();


#endif /* INC_FRAME_RING_BUFFER_H_ */
