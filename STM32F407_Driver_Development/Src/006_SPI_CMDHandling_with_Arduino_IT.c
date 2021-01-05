/*
 * 006_SPI_CMDHandling_with_Arduino_IT.c
 *
 *  Created on: Jan 5, 2021
 *      Author: Aakash
 */
#include "stm32f407xx.h"

SPI_Handle_t pSPIHandle;

int main()
{

}

void SPI1_IRQHandler(void)
{
	SPI_IRQHandler(&pSPIHandle);
}
