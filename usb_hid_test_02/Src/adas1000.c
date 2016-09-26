/*
 * adas1000.c
 *
 *  Created on: Aug 23, 2016
 *      Author: root
 */

#include "adas1000.h"
#include "adas1000_get_save_frame.h"

uint32_t *adas1000_read_frame()
{
    read_frame(frame);

    return frame;
}

