
#ifndef INC_ADAS1000_GET_SAVE_FRAME_H_
#define INC_ADAS1000_GET_SAVE_FRAME_H_

#include "stdint.h"
#include "adas1000.h"

#define CRC_POLYNOM (uint32_t)0x5d6dcb
#define CHECK_CONSTANT (uint32_t)0x15a0ba
#define ALL_ONES (uint32_t)0xffffffff
#define ALL_ZEROS (uint32_t)0x00000000
#define msb_mask (uint32_t)0x01000000
#define msb8_mask (uint8_t)0x80
#define lsb_mask (uint32_t)0x00000001

#define ADDRESS0 (uint32_t)0x40000000
#define ADDRESS1 (uint32_t)0x11000000
#define ADDRESS2 (uint32_t)0x12000000
#define ADDRESS3 (uint32_t)0x13000000
#define ADDRESS4 (uint32_t)0x14000000
#define ADDRESS5 (uint32_t)0x15000000
#define ADDRESS6 (uint32_t)0x1a000000
#define ADDRESS7 (uint32_t)0x1b000000
#define ADDRESS8 (uint32_t)0x1c000000
#define ADDRESS9 (uint32_t)0x1d000000
#define ADDRESS10 (uint32_t)0x06000000
#define ADDRESS11 (uint32_t)0x41000000

int new_frame_ready_flag;


uint32_t crc_calculation(uint32_t *message, int length, uint32_t polynomial, uint32_t preset, uint32_t extension);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

int read_frame(uint32_t *frame_buffer);


#endif /* INC_ADAS1000_GET_SAVE_FRAME_H_ */
