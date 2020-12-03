/*
 * 002_LED_with_Button.c
 *
 *  Created on: Nov 29, 2020
 *      Author: Aakash
 */


void delay(void)
{
	for(int i=0; i<= 250000; i++);
}

#include "stm32f407xx.h"

int main(void)
{

	GPIO_Handle_t gpioled, gpioBtn;

	gpioled.pGPIOx = GPIOD;
	gpioled.PinConfig.pinNumber = GPIO_PIN_NO_13;
	gpioled.PinConfig.PinMode = PIN_MODE_OUT;
	gpioled.PinConfig.PinOType = PIN_OTYPE_PP;
	gpioled.PinConfig.PinOSpeed = PIN_OSPEED_HIGH;
	gpioled.PinConfig.PinPuPd = PIN_PUPD_NONE;

	GPIO_PeriClkControl(GPIOD, ENABLE);
	GPIO_Init(gpioled);

	gpioBtn.pGPIOx = GPIOA;
	gpioBtn.PinConfig.pinNumber = GPIO_PIN_NO_0;
	gpioBtn.PinConfig.PinMode = PIN_MODE_IN;
	gpioBtn.PinConfig.PinOType = PIN_OTYPE_PP;
	gpioBtn.PinConfig.PinOSpeed = PIN_OSPEED_HIGH;
	gpioBtn.PinConfig.PinPuPd = PIN_PUPD_NONE;
	GPIO_PeriClkControl(GPIOA, ENABLE);
	GPIO_Init(gpioBtn);




	while(1)
	{
		while(!GPIO_ReadFromPin(GPIOA, GPIO_PIN_NO_0));
		delay();
	GPIO_TogglePin(GPIOD, GPIO_PIN_NO_13);
	}


}
