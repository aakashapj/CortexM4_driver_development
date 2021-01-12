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

void GPIO_Button(void)
{
	GPIO_Handle_t gpioBtn;
	gpioBtn.pGPIOx = GPIOA;
	gpioBtn.PinConfig.pinNumber = GPIO_PIN_NO_0;
	gpioBtn.PinConfig.PinMode = PIN_MODE_IN;
	gpioBtn.PinConfig.PinOType = PIN_OTYPE_PP;
	gpioBtn.PinConfig.PinOSpeed = PIN_OSPEED_HIGH;
	gpioBtn.PinConfig.PinPuPd = PIN_PUPD_NONE;
	GPIO_Init(&gpioBtn);
}

//Pins

/*
 * NSS - PB12
 * SCK - PB13
 * MISO - PB14
 * MOSI - PB15
 */

void SPI_GPIOInit(void)
{
	GPIO_Handle_t GPIOHandle;
	GPIOHandle.pGPIOx 				= GPIOB;
	GPIOHandle.PinConfig.PinMode 	= PIN_MODE_ALT;
	GPIOHandle.PinConfig.PinALTFn 	= PIN_ALTFN_5;
	GPIOHandle.PinConfig.PinOSpeed	= PIN_OSPEED_HIGH;
	GPIOHandle.PinConfig.PinOType	= PIN_OTYPE_PP;
	GPIOHandle.PinConfig.PinPuPd	= PIN_PUPD_PU;

	//NSS Slave Select Pin
	GPIOHandle.PinConfig.pinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&GPIOHandle);

	//SCK Serial Clock
	GPIOHandle.PinConfig.pinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&GPIOHandle);

	//MISO Master In Slave Out
	GPIOHandle.PinConfig.pinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&GPIOHandle);

	//MOSI Master Out Slave In
	GPIOHandle.PinConfig.pinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&GPIOHandle);

}

void SPI1_Init(void)
{


	SPIHandle.pSPIx 						= SPI2;
	SPIHandle.SPIConfig.SPIDeviceMode	 	= SPI_MODE_MASTER;
	SPIHandle.SPIConfig.SPIDFF 				= SPI_DFF_8BIT;
	SPIHandle.SPIConfig.SPIBusConfig 		= SPI_BUS_FULL_DUPLEX;
	SPIHandle.SPIConfig.SPIClkSpeed			= SPI_CLK_SPEED_DIV8;
	SPIHandle.SPIConfig.SPISSM 				= SPI_SSM_DI;
	SPIHandle.SPIConfig.SPICPHA				= SPI_CPHA_FIRST;
	SPIHandle.SPIConfig.SPICPOL				= SPI_CPOL_LOW;

	SPI_Init(&SPIHandle);
}

uint8_t DummyRead;
uint8_t DummySend = 0xff;
uint8_t commandcode = 0;
uint8_t ACKORNACK;

//char user[] = "Hello World";


extern void initialise_monitor_handles(void);

int main()
{
	initialise_monitor_handles();

	printf("Hello World\n");

	SPI_GPIOInit();

	GPIO_Button();

	SPI1_Init();

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
	SPI_SendData(&SPIHandle,&commandcode, 1);
	SPI_ReceiveData(&SPIHandle, &DummyRead, 1);

	//Getting ACK Back
	SPI_SendData(&SPIHandle, &DummySend, 1);
	SPI_ReceiveData(&SPIHandle, &ACKORNACK, 1);


	if(ACKORNACK == ACK)
	{
		printf("Acknowledged LED CONTROL\n");
				//Sending Pin Number
		SPI_SendData(&SPIHandle, &Led_pin, 1);
		SPI_ReceiveData(&SPIHandle, &DummyRead, 1);
			if(Led_st == LED_ON)
			{
				//Sending Value
				SPI_SendData(&SPIHandle, &Led_st, 1);
				SPI_ReceiveData(&SPIHandle, &DummyRead, 1);

				printf("Command executed: LED ON\n");
			}else if(Led_st == LED_OFF)
			{
				//Sending Value
				SPI_SendData(&SPIHandle, &Led_st, 1);
				SPI_ReceiveData(&SPIHandle, &DummyRead, 1);

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
	SPI_SendData(&SPIHandle,&commandcode, 1);
	SPI_ReceiveData(&SPIHandle, &DummyRead, 1);

	//Getting ACK Back
	SPI_SendData(&SPIHandle, &DummySend, 1);
	SPI_ReceiveData(&SPIHandle, &ACKORNACK, 1);

	if(ACKORNACK == ACK)
	{
		printf("Acknowledged SENSOR CONTROL\n");
		uint8_t AnaSen_Read;
		//Sending Command
		SPI_SendData(&SPIHandle, &Ana_pin, 1);
		SPI_ReceiveData(&SPIHandle, &DummyRead, 1);

		delay();

		//Getting Response
		SPI_SendData(&SPIHandle, &DummySend, 1);
		SPI_ReceiveData(&SPIHandle, &AnaSen_Read, 1);

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
	SPI_SendData(&SPIHandle, &commandcode, 1);
	SPI_ReceiveData(&SPIHandle, &DummyRead, 1);

	//Ack Receiving
	SPI_SendData(&SPIHandle, &DummySend, 1);
	SPI_ReceiveData(&SPIHandle, &ACKORNACK, 1);

	if(ACKORNACK == ACK)
	{
		printf("Acknowledged COMMAND PRINT\n");

		//Sending Length of data String
		SPI_SendData(&SPIHandle, &len, 1);

		//Sending String
		SPI_SendData(&SPIHandle, data, len);
	}

	printf("---------------------------------------\n");

	//Reading Board Id

	while(!GPIO_ReadFromPin(GPIOA, GPIO_PIN_NO_0));
	delay();

	commandcode = COMMAND_ID_READ;
	uint8_t BoardID[15];
	int i;
	uint8_t Id_Len;

	//Sending Command Code
	SPI_SendData(&SPIHandle, &commandcode, 1);
	SPI_ReceiveData(&SPIHandle, &DummyRead, 1);

	//Receiving Ack Byte
	SPI_SendData(&SPIHandle, &DummySend, 1);
	SPI_ReceiveData(&SPIHandle, &ACKORNACK, 1);


	if(ACKORNACK == ACK)
	{
		printf("Acknowledged COMMAND BOARD ID\n");

		SPI_SendData(&SPIHandle, &DummySend, 1);
		SPI_ReceiveData(&SPIHandle, &Id_Len, 1);

		for(i=0; i< Id_Len; i++)
		{
			SPI_SendData(&SPIHandle, &DummySend, 1);
			SPI_ReceiveData(&SPIHandle, &BoardID[i], 1);
		}
		BoardID[Id_Len+1] = '\0';

		printf("Board Id: %s \n", BoardID);
	}

	printf("---------------------------------------\n");


	SPI_PeriControl(SPI2, DISABLE);
	}

}

















