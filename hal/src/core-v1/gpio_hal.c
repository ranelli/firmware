/**
 ******************************************************************************
 * @file    gpio_hal.c
 * @authors Satish Nair, Brett Walach
 * @version V1.0.0
 * @date    13-Sept-2014
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

/* Includes -----------------------------------------------------------------*/
#include "gpio_hal.h"
#include "pinmap_impl.h"
#include "stm32f10x.h"
#include <stddef.h>

/* Private typedef ----------------------------------------------------------*/

/* Private define -----------------------------------------------------------*/

/* Private macro ------------------------------------------------------------*/

/* Private variables --------------------------------------------------------*/

PinMode digitalPinModeSaved = PIN_MODE_NONE;

/* Extern variables ---------------------------------------------------------*/

/* Private function prototypes ----------------------------------------------*/

inline bool is_valid_pin(pin_t pin)
{
    return pin<TOTAL_PINS;
}

PinMode HAL_Get_Pin_Mode(pin_t pin) 
{
    return (!is_valid_pin(pin)) ? PIN_MODE_NONE : PIN_MAP[pin].pin_mode;
}

PinFunction HAL_Validate_Pin_Function(pin_t pin, PinFunction pinFunction)
{
    if (!is_valid_pin(pin))
        return PF_NONE;
    if (pinFunction==PF_ADC && PIN_MAP[pin].adc_channel!=ADC_CHANNEL_NONE)
        return PF_ADC;
    if (pinFunction==PF_TIMER && PIN_MAP[pin].timer_peripheral!=NULL)
        return PF_TIMER;
    return PF_DIO;
}

/*
 * @brief Set the mode of the pin to OUTPUT, INPUT, INPUT_PULLUP, 
 * or INPUT_PULLDOWN
 */
void HAL_Pin_Mode(pin_t pin, PinMode setMode)
{

  GPIO_TypeDef *gpio_port = PIN_MAP[pin].gpio_peripheral;
  pin_t gpio_pin = PIN_MAP[pin].gpio_pin;

  GPIO_InitTypeDef GPIO_InitStructure;

  if (gpio_port == GPIOA )
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  }
  else if (gpio_port == GPIOB )
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  }

  GPIO_InitStructure.GPIO_Pin = gpio_pin;

  switch (setMode)
  {

  case OUTPUT:
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    PIN_MAP[pin].pin_mode = OUTPUT;
    break;

  case INPUT:
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    PIN_MAP[pin].pin_mode = INPUT;
    break;

  case INPUT_PULLUP:
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    PIN_MAP[pin].pin_mode = INPUT_PULLUP;
    break;

  case INPUT_PULLDOWN:
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    PIN_MAP[pin].pin_mode = INPUT_PULLDOWN;
    break;

  case AF_OUTPUT_PUSHPULL:  //Used internally for Alternate Function Output PushPull(TIM, UART, SPI etc)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    PIN_MAP[pin].pin_mode = AF_OUTPUT_PUSHPULL;
    break;

  case AF_OUTPUT_DRAIN:   //Used internally for Alternate Function Output Drain(I2C etc)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    PIN_MAP[pin].pin_mode = AF_OUTPUT_DRAIN;
    break;

  case AN_INPUT:        //Used internally for ADC Input
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    PIN_MAP[pin].pin_mode = AN_INPUT;
    break;

  default:
    break;
  }

  GPIO_Init(gpio_port, &GPIO_InitStructure);
}

/*
 * @brief Saves a pin mode to be recalled later.
 */
void HAL_GPIO_Save_Pin_Mode(PinMode mode)
{
  digitalPinModeSaved = mode;
}

/*
 * @brief Recalls a saved pin mode.
 */
PinMode HAL_GPIO_Recall_Pin_Mode()
{
  return digitalPinModeSaved;
}

/*
 * @brief Sets a GPIO pin to HIGH or LOW.
 */
void HAL_GPIO_Write(uint16_t pin, uint8_t value)
{
  //If the pin is used by analogWrite, we need to change the mode
  if(PIN_MAP[pin].pin_mode == AF_OUTPUT_PUSHPULL)
  {
    HAL_Pin_Mode(pin, OUTPUT);
  }

  if(value == 0)
  {
    PIN_MAP[pin].gpio_peripheral->BRR = PIN_MAP[pin].gpio_pin;
  } 
  else
  {
    PIN_MAP[pin].gpio_peripheral->BSRR = PIN_MAP[pin].gpio_pin;
  }
}

/*
 * @brief Reads the value of a GPIO pin. Should return either 1 (HIGH) or 0 (LOW).
 */
int32_t HAL_GPIO_Read(uint16_t pin)
{
  if(PIN_MAP[pin].pin_mode == AN_INPUT)
  {
    PinMode pm = HAL_GPIO_Recall_Pin_Mode();
    if(pm == PIN_MODE_NONE)
    {
      return 0;
    }
    else
    {
      // Restore the PinMode after calling analogRead() on same pin earlier
      HAL_Pin_Mode(pin, pm);
    }
  }

  if(PIN_MAP[pin].pin_mode == OUTPUT)
  {
    return GPIO_ReadOutputDataBit(PIN_MAP[pin].gpio_peripheral, PIN_MAP[pin].gpio_pin);
  }

  return GPIO_ReadInputDataBit(PIN_MAP[pin].gpio_peripheral, PIN_MAP[pin].gpio_pin);
}
