/*
 * stm32f407_i2c_driver.c
 *
 *  Created on: Jan 16, 2021
 *      Author: Aakash
 */

#ifndef SRC_STM32F407_I2C_DRIVER_C_
#define SRC_STM32F407_I2C_DRIVER_C_

#include "stm32f407xx.h"

uint16_t AHB[] = {2,4,8,16,64,128,256,512};
uint8_t APB[] = {2,4,8,16};

static void I2C_AckControl(I2C_RegDef_t *pI2C, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pI2C->CR1 |= (1 << I2C_CR1_ACK);
	}else
	{
		pI2C->CR1 |= (1 << I2C_CR1_ACK);
	}
}

uint32_t RCC_GetPclkValue(void)
{
	uint32_t pclk1, sysclk;

	uint8_t temp,ahbp,apb1p;

	temp = ((RCC->CFGR >> 2) & 0x3);
	if(temp == 0)
	{
		sysclk = 16000000;
	}else if(temp == 1)
	{
		sysclk = 8000000;
	}else if(temp == 2)
	{
		//PLL Configuration
	}

	temp = ((RCC->CFGR >> 4) & 0xf);
	if(temp < 8)
	{
		ahbp = 1;
	}else if(temp >= 8)
	{
		ahbp = AHB[temp - 8];
	}

	temp = ((RCC->CFGR >> 10) & 0x7);
	if(temp < 2)
	{
		apb1p = 1;
	}else if(temp >= 2)
	{
		apb1p = APB[temp - 4];
	}

	pclk1 = (sysclk/ahbp)/apb1p;

	return pclk1;

}

void I2C_PeriClkControl(I2C_RegDef_t *pI2C, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pI2C == I2C1)
		{
			I2C_PeriClkControl(I2C1, ENABLE);
		}else if(pI2C == I2C2)
		{
			I2C_PeriClkControl(I2C2, ENABLE);
		}else if(pI2C == I2C3)
		{
			I2C_PeriClkControl(I2C3, ENABLE);
		}
	}else
	{
		if(pI2C == I2C1)
		{
			I2C_PeriClkControl(I2C1, DISABLE);
		}else if(pI2C == I2C2)
		{
			I2C_PeriClkControl(I2C2, DISABLE);
		}else if(pI2C == I2C3)
		{
			I2C_PeriClkControl(I2C3, DISABLE);
		}
	}
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	//1. I2C Clock Peripheral Clock Enabling
	I2C_PeriClkControl(pI2CHandle->pI2C, ENABLE);

	//2. Ack Control configuration
	if(pI2CHandle->I2C_PinConfig.I2C_ACKControl == I2C_ACKCONTROL_EN)
	{
		I2C_AckControl(pI2CHandle->pI2C, ENABLE);
	}else if(pI2CHandle->I2C_PinConfig.I2C_ACKControl == I2C_ACKCONTROL_DI)
	{
		I2C_AckControl(pI2CHandle->pI2C, DISABLE);
	}

	//3. Peripheral Clock Frequency Control Configuration
	pI2CHandle->pI2C->CR2 |= ((RCC_GetPclkValue()/1000000U) & 0x3f);
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
