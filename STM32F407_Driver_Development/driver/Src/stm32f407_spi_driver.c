/*
 * stm32f407_spi_driver.c
 *
 *  Created on: Dec 7, 2020
 *      Author: Aakash
 */

#include "stm32f407xx.h"

static void spi_txe_interrupt_handler(SPI_Handle_t *pSPIHandle);
static void spi_rxe_interrupt_handler(SPI_Handle_t *pSPIHandle);
static void spi_ovr_interrupt_handler(SPI_Handle_t *pSPIHandle);

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

void SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	//Checking Status of SPI Communication
	uint8_t status = pSPIHandle->SPI_Status_g;

	if(status != SPI_BUSY_TX)
	{
		//Status SPI Busy in Transmission
		pSPIHandle->SPI_Status_g = SPI_BUSY_TX;

		//Sending Variable Values in Global Variable
		pSPIHandle->pTxBuffer_g = pTxBuffer;
		pSPIHandle->TxLen_g = Len;

		//Enabling SPI Transmission Interrupt
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);
	}
}

void SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{

}

void SPI_IRQHandler(SPI_Handle_t *pSPIHandle)
{
	 spi_txe_interrupt_handler(pSPIHandle);

}

static void spi_txe_interrupt_handler(SPI_Handle_t *pSPIHandle)
{
	while(pSPIHandle->TxLen_g > 0)
	{
		if(pSPIHandle->SPIConfig.SPIDFF == SPI_DFF_16BIT)
		{
			pSPIHandle->pSPIx->DR = *(pSPIHandle->pTxBuffer_g);
			pSPIHandle->pTxBuffer_g++;
			pSPIHandle->pTxBuffer_g++;
			pSPIHandle->TxLen_g--;
			pSPIHandle->TxLen_g--;
		}else if(pSPIHandle->SPIConfig.SPIDFF == SPI_DFF_8BIT)
		{
			pSPIHandle->pSPIx->DR = *(pSPIHandle->pTxBuffer_g);
			pSPIHandle->pTxBuffer_g++;
			pSPIHandle->TxLen_g--;
		}
	}

	if(!pSPIHandle->TxLen_g)
	{
		CloseTransmission(pSPIHandle);
	}
}

static void spi_rxe_interrupt_handler(SPI_Handle_t *pSPIHandle)
{

}

static void spi_ovr_interrupt_handler(SPI_Handle_t *pSPIHandle)
{

}

void CloseTransmission(SPI_Handle_t *pSPIHandle)
{
	//Disabling Interrupt
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);

	//Clearing Buffer and Structure Data
	pSPIHandle->TxLen_g = 0;
	pSPIHandle->pTxBuffer_g = NULL;

	//Making SPI Ready for next Communication
	pSPIHandle->SPI_Status_g = SPI_READY;
}

void CloseReception(SPI_Handle_t *pSPIHandle)
{
	//Disabling Interrupt
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);

	//Clearing Buffer and Structure Data
	pSPIHandle->RxLen_g = 0;
	pSPIHandle->pRxBuffer_g = NULL;

	//Making SPI Ready for next Communication
	pSPIHandle->SPI_Status_g = SPI_READY;
}
