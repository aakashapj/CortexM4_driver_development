/*
 * stm32f407xx.h
 *
 *  Created on: Nov 11, 2020
 *      Author: Aakash
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#define __vo 	volatile
#include <stdint.h>
#include <string.h>
#include <stdio.h>



/*********************Base Address Macros***************************/
/*
 * Base Address of Processor Memories
 */

#define FLASH		0x08000000U
#define SRAM		0x20000000U
#define SYSTEM		0x1FFF0000U

/*
 * Peripheral Bus Addresses
 */
#define APB1_BASEADDR	0x40000000
#define APB2_BASEADDR	0x40010000
#define AHB1_BASEADDR	0x40020000
#define AHB2_BASEADDR	0x50000000
#define AHB3_BASEADDR 	0xA0000000

/*
 * NVIC Base Address
 */
#define NVIC_ISER		(uint32_t*)0xE000E100
#define NVIC_ICER		(uint32_t*)0XE000E180



/******************Peripheral Base Address******************/

/*
 * General Peripheral Input Output Base address
 */
#define GPIOA_BASEADDR	(AHB1_BASEADDR + 0x0000)
#define GPIOB_BASEADDR	(AHB1_BASEADDR + 0x0400)
#define GPIOC_BASEADDR	(AHB1_BASEADDR + 0x0800)
#define GPIOD_BASEADDR	(AHB1_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR	(AHB1_BASEADDR + 0x1000)
#define GPIOF_BASEADDR	(AHB1_BASEADDR + 0x1400)
#define GPIOG_BASEADDR	(AHB1_BASEADDR + 0x1800)
#define GPIOH_BASEADDR	(AHB1_BASEADDR + 0x1C00)

/*
 * Reset and Clock Control Base Address
 */
#define RCC_BASEADDR	(AHB1_BASEADDR + 0x3800)

/*
 * External Interrupt Base Address
 */
#define EXTI_BASEADDR	(APB2_BASEADDR + 0x3C00)

/*
 * System Configuration Base Address
 */
#define SYSCFG_BASEADDR (APB2_BASEADDR + 0x3800)

/*
 * Serial Peripheral Interface Base Address
 */
#define SPI1_BASEADDR	(APB2_BASEADDR + 0x3000)
#define SPI2_BASEADDR	(APB1_BASEADDR + 0x3800)
#define SPI3_BASEADDR	(APB1_BASEADDR + 0x3C00)
#define SPI4_BASEADDR	(APB2_BASEADDR + 0x3400)

/*
 * Inter Integrated Circuit  Base Address
 */
#define I2C1_BASEADDR	(APB1_BASEADDR + 0x5400)
#define I2C2_BASEADDR	(APB1_BASEADDR + 0x5800)
#define I2C3_BASEADDR	(APB1_BASEADDR + 0x5C00)

/****************Peripheral Register Definition****************/

/*
 * Reset and Clock Control Register Definition
 */
typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	 uint32_t Reserved;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	 uint32_t Reserved0[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	 uint32_t Reserved1;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	 uint32_t Reserved2[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	 uint32_t Reserved3;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	 uint32_t Reserved4[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	 uint32_t Reserved5[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
}RCC_RegDef_t;

/*
 * General Purpose Input and Output Register Definition
 */

typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];

}GPIO_RegDef_t;

/*
 * External Interrupt Register Definition
 */

typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;

/*
 * System Configuration Register Definition
 */
typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	__vo uint32_t Reserved[2];
	__vo uint32_t CMPCR;
}SYSCFG_RegDef_t;

/*
 * Serial Peripheral Interface Register Definition
 */
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;
}SPI_RegDef_t;

/*
 * Inter Integrated Circuit Register Definition
 */
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t OAR1;
	__vo uint32_t OAR2;
	__vo uint32_t DR;
	__vo uint32_t SR1;
	__vo uint32_t SR2;
	__vo uint32_t CCR;
	__vo uint32_t TRISE;
	__vo uint32_t FLTR;
}I2C_RegDef_t;

/*************Base Address Type Casted to Peripheral Register Definition**********/

/*
 * Reset and Clock Control type casted Base addr
 */

#define RCC			((RCC_RegDef_t*)RCC_BASEADDR)

/*
 * GPIO Register Definition type casted to Base address
 */
#define GPIOA		((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB		((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC		((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD		((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE		((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF		((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG		((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH		((GPIO_RegDef_t*)GPIOH_BASEADDR)

/*
 * EXTI Register Definition type casted to Base address
 */
#define EXTI		((EXTI_RegDef_t*)EXTI_BASEADDR)

/*
 * System Configuration Register Definition type casted to Base address
 */
#define SYSCFG 		((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

/*
 * Serial Peripheral Interface Register Definition type Casted to Base Address
 */
#define SPI1		((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2		((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3		((SPI_RegDef_t*)SPI3_BASEADDR)

/*
 * Inter Integrated Circuit Register Definition type Casted to Base Address
 */
#define I2C1		((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2		((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3		((I2C_RegDef_t*)I2C3_BASEADDR)

/************* Peripheral Clock Enable Macros *************/
/*
 * GPIO Enable Macros
 */
#define GPIOA_PCLK_EN()  		(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()  		(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()  		(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()  		(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()  		(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()  		(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()  		(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()  		(RCC->AHB1ENR |= (1 << 7))

/*
 * System Configuration Clock Enable
 */
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1 << 14))

/*
 * SPI Clock Enable
 */
#define SPI1_PCLK_EN()			(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()			(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()			(RCC->APB1ENR |= (1 << 15))

/*
 * I2C Clock Enable
 */
#define I2C1_PCLK_EN()			(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()			(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()			(RCC->APB1ENR |= (1 << 23))

/************* Peripheral Clock Disable Macros*************/
/*
 * GPIO Disable Macros
 */
#define GPIOA_PCLK_DI()  		(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()  		(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()  		(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()  		(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()  		(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()  		(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()  		(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()  		(RCC->AHB1ENR &= ~(1 << 7))

/*
 * System Configuration Clock Enable
 */
#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 14))

/*
 * SPI Clock Enable
 */
#define SPI1_PCLK_DI()			(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 15))

/*
 * I2C Clock Enable
 */
#define I2C1_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 23))

/*********************Peripheral Reset Macros*********************/
/*
 * Peripheral Reset
 */
#define GPIOA_REG_RST()		do{RCC->AHB1RSTR |= (1 << 0); RCC->AHB1RSTR &= ~(1 << 0);}while(0)
#define GPIOB_REG_RST()		do{RCC->AHB1RSTR |= (1 << 1); RCC->AHB1RSTR &= ~(1 << 1);}while(0)
#define GPIOC_REG_RST()		do{RCC->AHB1RSTR |= (1 << 2); RCC->AHB1RSTR &= ~(1 << 2);}while(0)
#define GPIOD_REG_RST()		do{RCC->AHB1RSTR |= (1 << 3); RCC->AHB1RSTR &= ~(1 << 3);}while(0)
#define GPIOE_REG_RST()		do{RCC->AHB1RSTR |= (1 << 4); RCC->AHB1RSTR &= ~(1 << 4);}while(0)
#define GPIOF_REG_RST()		do{RCC->AHB1RSTR |= (1 << 5); RCC->AHB1RSTR &= ~(1 << 5);}while(0)
#define GPIOG_REG_RST()		do{RCC->AHB1RSTR |= (1 << 6); RCC->AHB1RSTR &= ~(1 << 6);}while(0)
#define GPIOH_REG_RST()		do{RCC->AHB1RSTR |= (1 << 7); RCC->AHB1RSTR &= ~(1 << 7);}while(0)

/*
 * Interrupt Position Macros
 */
#define IRQ_LINE_EXTI0		6
#define IRQ_LINE_EXTI1		7
#define IRQ_LINE_EXTI2		8
#define IRQ_LINE_EXTI3		9
#define IRQ_LINE_EXTI4		10

#define IRQ_LINE_SPI1		35
#define IRQ_LINE_SPI2		36

#define IRQ_LINE_I2C1_EV	31
#define IRQ_LINE_I2C1_ER	32

#define IRQ_LINE_I2C2_EV	33
#define IRQ_LINE_I2C2_ER	34

/*
 * Some Other Macros
 */
#define ENABLE 		1
#define DISABLE 	0
#define SET			ENABLE
#define RESET		DISABLE




/** Peripheral Headers **/
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"
#include "stm32f407xx_i2c_driver.h"




#endif /* INC_STM32F407XX_H_ */
