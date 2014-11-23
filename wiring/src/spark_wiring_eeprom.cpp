/**
 ******************************************************************************
 * @file    spark_wiring_eeprom.cpp
 * @author  Satish Nair
 * @version V1.0.0
 * @date    10-April-2014
 * @brief   This file provides all the EEPROM emulation functions.
 * 			Based on ST Application Note for STM32: AN2594
 * 			http://www.st.com/st-web-ui/static/active/en/resource/
 * 			technical/document/application_note/CD00165693.pdf
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

/* Includes ------------------------------------------------------------------*/
#include "spark_wiring_eeprom.h"

/* Arduino Compatibility EEPROM methods */
EEPROMClass::EEPROMClass()
{
  HAL_EEPROM_Init();
}

uint8_t EEPROMClass::read(int address)
{
  return HAL_EEPROM_Read(address);
}

void EEPROMClass::write(int address, uint8_t value)
{
  HAL_EEPROM_Write(address, value);
}

EEPROMClass EEPROM;
