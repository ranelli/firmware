/**
 ******************************************************************************
 * @file    deviceid_hal.h
 * @author  Matthew McGowan
 * @version V1.0.0
 * @date    25-Sept-2014
 * @brief
 ******************************************************************************
  Copyright (c) 2013-14 Spark Labs, Inc.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */

#ifndef DEVICEID_HAL_H
#define	DEVICEID_HAL_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Fetches the unique ID for this device.
 * 
 * @param dest      The buffer to receive the device ID
 * @param destLen   The maximum length of the buffer. Can be 0.
 * @return          The number of bytes in the device ID. This is independent 
 *                  of the buffer size. 
 * 
 * To find out the size of the device ID, call this method with 
 * {@code destLen}==0.
 */        
unsigned HAL_device_ID(uint8_t* dest, unsigned destLen);


#ifdef	__cplusplus
}
#endif

#endif	/* DEVICEID_HAL_H */

