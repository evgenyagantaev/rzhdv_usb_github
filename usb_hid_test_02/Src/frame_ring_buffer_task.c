/*
 * frame_ring_buffer_task.c
 *
 *  Created on: Aug 23, 2016
 *      Author: root
 */

#include "frame_ring_buffer_task.h"

#include "gpio.h"

void frame_ring_buffer_task()
{
    if(get_received_frames_counter() < timer250hz_get_tick())
    {

        frame_ring_buffer_push(adas1000_read_frame(), FRAME_LENGTH);

        //int ecg = (ecg_ring_buffer[0][1]&((uint32_t)0x00ffffff)) - (ecg_ring_buffer[0][3]&((uint32_t)0x00ffffff));
        //int ecg = ecg_ring_buffer[0][3]&((uint32_t)0x00ffffff);
        //int ecg = -primary_buffer[1]&((uint32_t)0x00ffffff);
        //sprintf(message, "%dI%d\r\n", ecg, ecg);

        // respiration **********************************************
        //int respiration = primary_buffer[7]&((uint32_t)0x00ffffff);
        //sprintf(message, "%dI%d\r\n", respiration, respiration);
        // respiration **********************************************


        //HAL_UART_Transmit(&huart1, message, strlen(message), 500);  // for production board
    }
}
