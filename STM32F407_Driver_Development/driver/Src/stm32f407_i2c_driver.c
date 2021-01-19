/*
 * stm32f407_i2c_driver.c
 *
 *  Created on: Jan 16, 2021
 *      Author: Aakash
 */

#ifndef SRC_STM32F407_I2C_DRIVER_C_
#define SRC_STM32F407_I2C_DRIVER_C_

#include "stm32f407xx.h"

void I2C_Init(I2C_Handle_t *pI2CHandle)
{

}

void I2C_DeInit(I2C_Handle_t *pI2CHandle)
{

}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t *SlaveAddr, uint8_t Sr)
{

}

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t *SlaveAddr, uint8_t Sr)
{

}

#endif /* SRC_STM32F407_I2C_DRIVER_C_ */
