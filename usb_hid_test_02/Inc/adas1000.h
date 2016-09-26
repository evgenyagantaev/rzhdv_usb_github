/*
 * adas1000.h
 *
 *  Created on: Aug 23, 2016
 *      Author: root
 */

#ifndef INC_ADAS1000_H_
#define INC_ADAS1000_H_

#include "stdint.h"

#define FRAME_LENGTH 12

// locals
static uint32_t frame[FRAME_LENGTH];

// methods
uint32_t *adas1000_read_frame();

#endif /* INC_ADAS1000_H_ */
