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
	SPI_RegDef_t SPIx;
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

#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
