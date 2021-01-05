/*
 * stm32f407xx_spi_driver.h
 *
 *  Created on: Dec 7, 2020
 *      Author: Aakash
 */

#ifndef INC_STM32F407XX_SPI_DRIVER_H_
#define INC_STM32F407XX_SPI_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t SPIDeviceMode;
	uint8_t SPIClkSpeed;
	uint8_t SPIBusConfig;
	uint8_t SPISSM;
	uint8_t SPIDFF;
	uint8_t SPICPOL;
	uint8_t SPICPHA;
}SPI_Config_t;

typedef struct
{
	SPI_Config_t SPIConfig;
	SPI_RegDef_t *pSPIx;
	uint8_t *pTxBuffer_g;
	uint8_t *pRxBuffer_g;
	uint32_t TxLen_g;
	uint32_t RxLen_g;
	uint8_t SPI_Status_g;
}SPI_Handle_t;

/****************** Serial Peripheral Interface User Macros ************/

#define SPI_MODE_MASTER				1
#define SPI_MODE_SLAVE				0

#define SPI_BUS_SIMPLEX				0
#define SPI_BUS_FULL_DUPLEX			1
#define SPI_BUS_HALF_DUPLEX			2

#define SPI_DFF_8BIT				0
#define SPI_DFF_16BIT				1

#define SPI_SSM_EN					1
#define SPI_SSM_DI					0

#define SPI_CLK_SPEED_DIV2			0
#define SPI_CLK_SPEED_DIV4			1
#define SPI_CLK_SPEED_DIV8			2
#define SPI_CLK_SPEED_DIV16			3
#define SPI_CLK_SPEED_DIV32			4
#define SPI_CLK_SPEED_DIV64			5
#define SPI_CLK_SPEED_DIV128		6
#define SPI_CLK_SPEED_DIV256		7

#define SPI_CPOL_LOW				0
#define SPI_CPOL_HIGH				1

#define SPI_CPHA_FIRST				0
#define SPI_CPHA_SECOND				1

/************SPI Control Register 1 Bit Position Macros**********/
#define SPI_CR1_CPHA				0
#define SPI_CR1_CPOL    			1
#define SPI_CR1_MSTR   				2
#define SPI_CR1_BR  				3
#define SPI_CR1_SPE 				6
#define SPI_CR1_LSBFIRST  			7
#define SPI_CR1_SSI       			8
#define SPI_CR1_SSM       			9
#define SPI_CR1_RXONLY    			10
#define SPI_CR1_DFF       			11
#define SPI_CR1_CRCNEXT   			12
#define SPI_CR1_CRCEN     			13
#define SPI_CR1_BIDIOE    			14
#define SPI_CR1_BIDIMODE  			15

/************SPI Control Register 2 Bit Position Macros**********/
#define SPI_CR2_RXDMAEN				0
#define SPI_CR2_TXDMAEN				1
#define SPI_CR2_SSOE				2
#define SPI_CR2_FRF					4
#define SPI_CR2_ERRIE				5
#define SPI_CR2_RXNEIE				6
#define SPI_CR2_TXEIE				7

/************SPI Status Register Bit Position Macros**********/
#define SPI_SR_RXNE					0
#define SPI_SR_TXE					1
#define SPI_SR_CHSIDE				2
#define SPI_SR_UDR					3
#define SPI_SR_CRCERR				4
#define SPI_SR_MODF					5
#define SPI_SR_OVR					6
#define SPI_SR_BSY					7
#define SPI_SR_FRE					8

/**************SPI Communication Status Macros*****************/
#define SPI_READY					0
#define SPI_BUSY_TX					1
#define SPI_BUSY_RX					2

/************SPI Driver Function Prototype*******************/
void SPI_PeriClkControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

void SPI_SendData(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);

void SPI_IRQHandler(SPI_Handle_t *pSPIHandle);

void SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);

void CloseTransmission(SPI_Handle_t *pSPIHandle);
void CloseReception(SPI_Handle_t *pSPIHandle);

void SPI_SSOEControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
uint8_t SPI_FlagStatus(SPI_RegDef_t *pSPIx, uint8_t Flagname);


#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
