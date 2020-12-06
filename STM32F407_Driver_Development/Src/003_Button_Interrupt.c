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

}

void EXTI0_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_NO_0);
}
