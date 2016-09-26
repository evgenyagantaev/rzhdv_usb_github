/*
 * leadoff_status_obj.c
 *
 *  Created on: Sep 20, 2016
 *      Author: root
 */

#include "leadoff_status_obj.h"

void set_leadoff_status(uint8_t status)
{
	leadoff_status = status;
}
uint8_t get_leadoff_status()
{
	return leadoff_status;
}
