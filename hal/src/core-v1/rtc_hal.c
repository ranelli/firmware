/**
 ******************************************************************************
 * @file    rtc_hal.c
 * @author  Satish Nair, Brett Walach
 * @version V1.0.0
 * @date    12-Sept-2014
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

/* Includes ------------------------------------------------------------------*/
#include "rtc_hal.h"
#include "stm32f10x_rtc.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Extern variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

uint32_t HAL_RTC_Get_Counter(void)
{
  return RTC_GetCounter();
}

void HAL_RTC_Set_Counter(uint32_t value)
{
  RTC_WaitForLastTask();
  RTC_SetCounter(value);
  RTC_WaitForLastTask();
}

void HAL_RTC_Set_Alarm(uint32_t value)
{
  /* Set the RTC Alarm */
  RTC_SetAlarm(RTC_GetCounter() + value);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}
