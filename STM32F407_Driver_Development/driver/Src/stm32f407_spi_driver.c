/*
 * stm32f407_spi_driver.c
 *
 *  Created on: Dec 7, 2020
 *      Author: Aakash
 */

#include "stm32f407xx.h"


/*
 * SPI Flag Status Function
 */
uint8_t SPI_FlagStatus(SPI_RegDef_t *pSPIx, uint8_t Flagname)
{
	if(pSPIx->SR & (1 << Flagname))
	{
		return SET;
	}
	return RESET;
}

/*
 * SPI Peripheral Enable
 */
void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

/*
 * Software Slave Output Control Function
 */
void SPI_SSOEControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	}else
	{
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}
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
	//SPI clock Enable
	SPI_PeriClkControl(pSPIHandle->pSPIx, ENABLE);

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
	pSPIHandle->pSPIx->CR1 |= tempreg;

}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

}

void SPI_SendData(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		while(!SPI_FlagStatus(pSPIHandle->pSPIx, SPI_SR_TXE));
		if(pSPIHandle->SPIConfig.SPIDFF == SPI_DFF_8BIT)
		{
			pSPIHandle->pSPIx->DR = *pTxBuffer;
			pTxBuffer++;
			Len--;

		}else if(pSPIHandle->SPIConfig.SPIDFF == SPI_DFF_16BIT)
		{
			pSPIHandle->pSPIx->DR = *((uint16_t*)pTxBuffer);
			pTxBuffer++;
			pTxBuffer++;
			Len--;
			Len--;
		}
	}
}

void SPI_ReceiveData(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		while(!SPI_FlagStatus(pSPIHandle->pSPIx, SPI_SR_RXNE));
		if(pSPIHandle->SPIConfig.SPIDFF == SPI_DFF_8BIT)
		{
			*pRxBuffer = pSPIHandle->pSPIx->DR;
			 pRxBuffer++;
			 Len--;
		}else if(pSPIHandle->SPIConfig.SPIDFF == SPI_DFF_16BIT)
		{
			*((uint16_t*)pRxBuffer) = pSPIHandle->pSPIx->DR;
			 pRxBuffer++;
			 pRxBuffer++;
			 Len--;
			 Len--;
		}
	}
}
