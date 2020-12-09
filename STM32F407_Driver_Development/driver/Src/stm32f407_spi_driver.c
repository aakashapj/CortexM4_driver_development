/*
 * stm32f407_spi_driver.c
 *
 *  Created on: Dec 7, 2020
 *      Author: Aakash
 */

#include "stm32f407xx.h"

/*
 * SPI Peripheral Clock Enable Function
 */
void SPI_PeriClkControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
	}
}

/*
 * SPI Initialization Function
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	uint32_t tempreg = 0;

	//1. Device Mode Configuration
	tempreg |= (pSPIHandle->SPIConfig.SPIDeviceMode << SPI_CR1_MSTR);

	//2. Bus Configuration
	if(pSPIHandle->SPIConfig.SPIBusConfig == SPI_BUS_FULL_DUPLEX)
	{
		//2 line Unidirectional Configuration
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);
	}else if(pSPIHandle->SPIConfig.SPIBusConfig == SPI_BUS_HALF_DUPLEX)
	{
		//1 line Bidirectional
		tempreg |= (1 << SPI_CR1_BIDIMODE);
	}else if(pSPIHandle->SPIConfig.SPIBusConfig == SPI_BUS_SIMPLEX)
	{
		//Receive Only
		//Bidi Mode in 2 line configuration
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);
		//Output Disable
		tempreg |= (1 << SPI_CR1_RXONLY);
	}

	//3. Baud Rate Configuration
	tempreg |= (pSPIHandle->SPIConfig.SPIClkSpeed << SPI_CR1_BR);

	//4. Software Save Management
	tempreg |= (pSPIHandle->SPIConfig.SPISSM << SPI_CR1_SSM);

	//5. Data Frame Formate
	tempreg |= (pSPIHandle->SPIConfig.SPIDFF << SPI_CR1_DFF);

	//6. SPI Clock Polarity Configuration
	tempreg |= (pSPIHandle->SPIConfig.SPICPOL << SPI_CR1_CPOL);

	//7. SPI Clock Phase Configuration
	tempreg |= (pSPIHandle->SPIConfig.SPICPHA << SPI_CR1_CPHA);

	//Putting Tempreg Value into the Control Register
	pSPIHandle->SPIx.CR1 |= tempreg;

}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

}

void SPI_SendData(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{

}

void SPI_ReceiveData(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{

}
