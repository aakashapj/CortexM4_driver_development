/*
 * 006_SPI_CMDHandling_with_Arduino_IT.c
 *
 *  Created on: Jan 5, 2021
 *      Author: Aakash
 */
#include "stm32f407xx.h"


#define NACK 0xA5
#define ACK 0xF5


//command codes
#define COMMAND_LED_CTRL          0x50
#define COMMAND_SENSOR_READ       0x51
#define COMMAND_LED_READ          0x52
#define COMMAND_PRINT           0x53
#define COMMAND_ID_READ         0x54

#define LED_ON     1
#define LED_OFF    0

#define LED_PIN		9

//arduino analog pins
#define ANALOG_PIN0   0
#define ANALOG_PIN1   1
#define ANALOG_PIN2   2
#define ANALOG_PIN3   3
#define ANALOG_PIN4   4


void delay()
{
	for(int i=0; i<= (400000); i++);
}

SPI_Handle_t SPIHandle;


void GPIOBTN(void)
{
	GPIO_Handle_t GPIOBTN;

	GPIOBTN.pGPIOx 				= GPIOA;
	GPIOBTN.PinConfig.pinNumber	= GPIO_PIN_NO_0;
	GPIOBTN.PinConfig.PinMode	= PIN_MODE_IN;
	GPIOBTN.PinConfig.PinOSpeed	= PIN_OSPEED_HIGH;
	GPIOBTN.PinConfig.PinOType	= PIN_OTYPE_PP;
	GPIOBTN.PinConfig.PinPuPd	= PIN_PUPD_NONE;

	GPIO_Init(&GPIOBTN);
}

//Pins

/*
 * NSS - PB12
 * SCK - PB13
 * MISO - PB14
 * MOSI - PB15
 */

void SPIGPIO(void)
{
	GPIO_Handle_t SPIGPIO;

	SPIGPIO.pGPIOx				= GPIOB;
	SPIGPIO.PinConfig.PinMode	= PIN_MODE_ALT;
	SPIGPIO.PinConfig.PinALTFn	= PIN_ALTFN_5;
	SPIGPIO.PinConfig.PinPuPd	= PIN_PUPD_PU;
	SPIGPIO.PinConfig.PinOType	= PIN_OTYPE_PP;
	SPIGPIO.PinConfig.PinOSpeed = PIN_OSPEED_FAST;

	//NSS
	SPIGPIO.PinConfig.pinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIGPIO);

	//SCK
	SPIGPIO.PinConfig.pinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIGPIO);

	//MISO
	SPIGPIO.PinConfig.pinNumber	= GPIO_PIN_NO_14;
	GPIO_Init(&SPIGPIO);

	//MOSI
	SPIGPIO.PinConfig.pinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIGPIO);
}

void SPI2Init(void)
{

	SPIHandle.pSPIx						= SPI2;
	SPIHandle.SPIConfig.SPIDeviceMode	= SPI_MODE_MASTER;
	SPIHandle.SPIConfig.SPIBusConfig 	= SPI_BUS_FULL_DUPLEX;
	SPIHandle.SPIConfig.SPIDFF 			= SPI_DFF_8BIT;
	SPIHandle.SPIConfig.SPIClkSpeed 	= SPI_CLK_SPEED_DIV8;
	SPIHandle.SPIConfig.SPICPOL			= SPI_CPOL_LOW;
	SPIHandle.SPIConfig.SPICPHA 		= SPI_CPHA_FIRST;
	SPIHandle.SPIConfig.SPISSM 			= SPI_SSM_DI;

	SPI_Init(&SPIHandle);
}

uint8_t DummyRead;
uint8_t DummySend = 0xff;
uint8_t commandcode = 0;
uint8_t ACKORNACK;

extern void initialise_monitor_handles(void);

int main()
{

	initialise_monitor_handles();

	printf("Hello World\n");

	GPIOBTN();

	SPIGPIO();

	SPI_IRQInterruptConfig(IRQ_LINE_SPI2, ENABLE);

	SPI2Init();

	SPI_SSOEControl(SPI2, ENABLE);

	while(1)
	{
		while(!GPIO_ReadFromPin(GPIOA, GPIO_PIN_NO_0));
		delay();


		SPI_PeriControl(SPI2, ENABLE);

		printf("SPI Peripheral Enable\n");

		printf("---------------------------------------\n");
		//LED Control

		commandcode = COMMAND_LED_CTRL;
		uint8_t Led_pin = LED_PIN;
		uint8_t Led_st = LED_ON;
		//Sending Command
		SPI_SendDataIT(&SPIHandle,&commandcode, 1);
		SPI_ReceiveDataIT(&SPIHandle, &DummyRead, 1);

		//Getting ACK Back
		SPI_SendDataIT(&SPIHandle, &DummySend, 1);
		SPI_ReceiveDataIT(&SPIHandle, &ACKORNACK, 1);


		if(ACKORNACK == ACK)
		{
			printf("Acknowledged LED CONTROL\n");
					//Sending Pin Number
			SPI_SendDataIT(&SPIHandle, &Led_pin, 1);
			SPI_ReceiveDataIT(&SPIHandle, &DummyRead, 1);
				if(Led_st == LED_ON)
				{
					//Sending Value
					SPI_SendDataIT(&SPIHandle, &Led_st, 1);
					SPI_ReceiveDataIT(&SPIHandle, &DummyRead, 1);

					printf("Command executed: LED ON\n");
				}else if(Led_st == LED_OFF)
				{
					//Sending Value
					SPI_SendDataIT(&SPIHandle, &Led_st, 1);
					SPI_ReceiveDataIT(&SPIHandle, &DummyRead, 1);

					printf("Command executed: LED OFF\n");
				}

		}

		printf("---------------------------------------\n");

		//Analog Sensor Data

		while(!GPIO_ReadFromPin(GPIOA, GPIO_PIN_NO_0));
		delay();

		commandcode = COMMAND_SENSOR_READ;
		uint8_t Ana_pin = ANALOG_PIN1;
		//Sending Command
		SPI_SendDataIT(&SPIHandle,&commandcode, 1);
		SPI_ReceiveDataIT(&SPIHandle, &DummyRead, 1);

		//Getting ACK Back
		SPI_SendDataIT(&SPIHandle, &DummySend, 1);
		SPI_ReceiveDataIT(&SPIHandle, &ACKORNACK, 1);

		if(ACKORNACK == ACK)
		{
			printf("Acknowledged SENSOR CONTROL\n");
			uint8_t AnaSen_Read;
			//Sending Command
			SPI_SendDataIT(&SPIHandle, &Ana_pin, 1);
			SPI_ReceiveDataIT(&SPIHandle, &DummyRead, 1);

			delay();

			//Getting Response
			SPI_SendDataIT(&SPIHandle, &DummySend, 1);
			SPI_ReceiveDataIT(&SPIHandle, &AnaSen_Read, 1);

			printf("Sensor Value: %d\n",AnaSen_Read);

		}

		printf("---------------------------------------\n");

		//Command Print

		while(!GPIO_ReadFromPin(GPIOA, GPIO_PIN_NO_0));
		delay();

		commandcode = COMMAND_PRINT;
		uint8_t data[] = "Hello World";
		uint8_t len = strlen((char*)data);

		//Command Code Send
		SPI_SendDataIT(&SPIHandle, &commandcode, 1);
		SPI_ReceiveDataIT(&SPIHandle, &DummyRead, 1);

		//Ack Receiving
		SPI_SendDataIT(&SPIHandle, &DummySend, 1);
		SPI_ReceiveDataIT(&SPIHandle, &ACKORNACK, 1);

		if(ACKORNACK == ACK)
		{
			printf("Acknowledged COMMAND PRINT\n");

			//Sending Length of data String
			SPI_SendDataIT(&SPIHandle, &len, 1);

			//Sending String
			SPI_SendDataIT(&SPIHandle, data, len);
		}

		printf("---------------------------------------\n");

		//Reading Board Id

		while(!GPIO_ReadFromPin(GPIOA, GPIO_PIN_NO_0));
		delay();

		commandcode = COMMAND_ID_READ;
		uint8_t BoardID[25];
		int i;
		uint8_t Id_Len;

		//Sending Command Code
		SPI_SendDataIT(&SPIHandle, &commandcode, 1);
		SPI_ReceiveDataIT(&SPIHandle, &DummyRead, 1);

		//Receiving Ack Byte
		SPI_SendDataIT(&SPIHandle, &DummySend, 1);
		SPI_ReceiveDataIT(&SPIHandle, &ACKORNACK, 1);


		if(ACKORNACK == ACK)
		{
			printf("Acknowledged COMMAND BOARD ID\n");

			SPI_SendDataIT(&SPIHandle, &DummySend, 1);
			SPI_ReceiveDataIT(&SPIHandle, &Id_Len, 1);

			for(i=0; i< Id_Len; i++)
			{
				SPI_SendDataIT(&SPIHandle, &DummySend, 1);
				SPI_ReceiveDataIT(&SPIHandle, &BoardID[i], 1);
			}
			BoardID[Id_Len+1] = '\0';

			printf("Board Id: %s \n", BoardID);
		}

		printf("---------------------------------------\n");


		SPI_PeriControl(SPI2, DISABLE);
	}

}

void SPI2_IRQHandler(void)
{
	SPI_IRQHandler(&SPIHandle);
}
