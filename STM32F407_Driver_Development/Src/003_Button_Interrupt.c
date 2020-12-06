/*
 * 003_Button_Interrup.c
 *
 *  Created on: Dec 1, 2020
 *      Author: Aakash
 */

void delay(int a)
{
	for(int i=0; i<= (571700*a); i++);
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
		gpioBtn.PinConfig.PinMode = PIN_MODE_RT;
		gpioBtn.PinConfig.PinOType = PIN_OTYPE_PP;
		gpioBtn.PinConfig.PinOSpeed = PIN_OSPEED_HIGH;
		gpioBtn.PinConfig.PinPuPd = PIN_PUPD_NONE;
		GPIO_PeriClkControl(GPIOA, ENABLE);
		GPIO_Init(gpioBtn);

		GPIO_IRQInterruptConfig(IRQ_LINE_EXTI0, ENABLE);

		while(1);

}

void EXTI0_IRQHandler(void)
{
	GPIO_TogglePin(GPIOD, GPIO_PIN_NO_13);
	delay(1);
	GPIO_IRQHandling(GPIO_PIN_NO_0);
}
