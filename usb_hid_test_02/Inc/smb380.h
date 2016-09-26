/*
 * smb380.h
 *
 *  Created on: Sep 2, 2016
 *      Author: root
 */

#ifndef INC_SMB380_H_
#define INC_SMB380_H_

#include "stdint.h"


void smb380_write_settings(); //write smb380 accelerometer settings
void smb380_read_xyz_rawdata(uint8_t *data); //read smb380 xyz h and l registers to buffer

#endif /* INC_SMB380_H_ */
