/*
 * 004_SPI_Comm_Master.c
 *
 *  Created on: Dec 15, 2020
 *      Author: Aakash
 */
#include"stm32f407xx.h"

void SPIGPIO_Init(void)
{
	GPIO_Handle_t GPIOHandle;
	GPIOHandle.pGPIOx = GPIOA;
	GPIOHandle.PinConfig.PinMode 	= PIN_MODE_ALT;
	GPIOHandle.PinConfig.PinALTFn 	= PIN_ALTFN_5;
	GPIOHandle.PinConfig.PinOSpeed	= PIN_OSPEED_HIGH;
	GPIOHandle.PinConfig.PinOType	= PIN_OTYPE_PP;
	GPIOHandle.PinConfig.PinPuPd	= PIN_PUPD_NONE;

	//NSS Slave Select Pin
	GPIOHandle.PinConfig.pinNumber = GPIO_PIN_NO_4;
	GPIO_Init(GPIOHandle);

	//SCK Serial Clock
	GPIOHandle.PinConfig.pinNumber = GPIO_PIN_NO_5;
	GPIO_Init(GPIOHandle);

	//MISO Master In Slave Out
	GPIOHandle.PinConfig.pinNumber = GPIO_PIN_NO_6;
	GPIO_Init(GPIOHandle);

	//MOSI Master Out Slave In
	GPIOHandle.PinConfig.pinNumber = GPIO_PIN_NO_7;
	GPIO_Init(GPIOHandle);

}

int main()
{

}
