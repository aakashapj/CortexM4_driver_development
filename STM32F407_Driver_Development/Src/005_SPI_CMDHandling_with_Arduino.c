/*
 * 005_SPI_CMDHandling_with_Arduino.c
 *
 *  Created on: Dec 21, 2020
 *      Author: Aakash
 */

#include"stm32f407xx.h"

#define NACK 0xA5
#define ACK 0xF5


//command codes
#define COMMAND_LED_CTRL          (uint8_t*)0x50
#define COMMAND_SENSOR_READ       (uint8_t*)0x51
#define COMMAND_LED_READ          (uint8_t*)0x52
#define COMMAND_PRINT           (uint8_t*)0x53
#define COMMAND_ID_READ         (uint8_t*)0x54

#define LED_ON     (uint8_t*)1
#define LED_OFF    (uint8_t*)0

void delay()
{
	for(int i=0; i<= (400000); i++);
}

SPI_Handle_t SPIHandle;

void GPIO_Button(void)
{
	GPIO_Handle_t gpioBtn;
	gpioBtn.pGPIOx = GPIOA;
	gpioBtn.PinConfig.pinNumber = GPIO_PIN_NO_0;
	gpioBtn.PinConfig.PinMode = PIN_MODE_IN;
	gpioBtn.PinConfig.PinOType = PIN_OTYPE_PP;
	gpioBtn.PinConfig.PinOSpeed = PIN_OSPEED_HIGH;
	gpioBtn.PinConfig.PinPuPd = PIN_PUPD_NONE;
	GPIO_Init(gpioBtn);
}


void SPI_GPIOInit(void)
{
	GPIO_Handle_t GPIOHandle;
	GPIOHandle.pGPIOx 				= GPIOA;
	GPIOHandle.PinConfig.PinMode 	= PIN_MODE_ALT;
	GPIOHandle.PinConfig.PinALTFn 	= PIN_ALTFN_5;
	GPIOHandle.PinConfig.PinOSpeed	= PIN_OSPEED_HIGH;
	GPIOHandle.PinConfig.PinOType	= PIN_OTYPE_PP;
	GPIOHandle.PinConfig.PinPuPd	= PIN_PUPD_PU;

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

void SPI1_Init(void)
{


	SPIHandle.pSPIx 						= SPI1;
	SPIHandle.SPIConfig.SPIDeviceMode	 	= SPI_MODE_MASTER;
	SPIHandle.SPIConfig.SPIDFF 				= SPI_DFF_8BIT;
	SPIHandle.SPIConfig.SPIBusConfig 		= SPI_BUS_FULL_DUPLEX;
	SPIHandle.SPIConfig.SPIClkSpeed			= SPI_CLK_SPEED_DIV8;
	SPIHandle.SPIConfig.SPISSM 				= SPI_SSM_DI;
	SPIHandle.SPIConfig.SPICPHA				= SPI_CPHA_FIRST;
	SPIHandle.SPIConfig.SPICPOL				= SPI_CPOL_LOW;

	SPI_Init(&SPIHandle);
}

uint8_t ReadData = 0;

int main()
{

	SPI_GPIOInit();

	GPIO_Button();

	SPI1_Init();

	SPI_SSOEControl(SPI1, ENABLE);

	while(1)
	{
	while(!GPIO_ReadFromPin(GPIOA, GPIO_PIN_NO_0));
	delay();

	SPI_PeriControl(SPI1, ENABLE);

	SPI_SendData(&SPIHandle, COMMAND_LED_CTRL, 1);
	SPI_ReceiveData(&SPIHandle,(uint8_t*)ReadData, 1);

	if(ReadData == ACK)
	{
		SPI_SendData(&SPIHandle, (uint8_t*)9, 1);
		SPI_SendData(&SPIHandle, LED_ON, 1);

	}
	SPI_PeriControl(SPI1, DISABLE);
	}

}

















