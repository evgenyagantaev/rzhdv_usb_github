/*
 * leadoff_status_obj.h
 *
 *  Created on: Sep 20, 2016
 *      Author: root
 */

#ifndef INC_LEADOFF_STATUS_OBJ_H_
#define INC_LEADOFF_STATUS_OBJ_H_

#include "stdint.h"

static uint8_t leadoff_status = 0;

void set_leadoff_status(uint8_t leadoff_status);
uint8_t get_leadoff_status();

#endif /* INC_LEADOFF_STATUS_OBJ_H_ */
