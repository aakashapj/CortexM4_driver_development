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
#define GPIOI_BASEADDR	(AHB1_BASEADDR + 0x1C00)

/*
 * Reset and Clock Control Base Address
 */
#define RCC_BASEADDR	(AHB1_BASEADDR + 0x3800)

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
	 uint32_t ReservED4[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	 uint32_t Reserveed5[2];
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
 * Peripheral Clock Enable Macros
 */

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
 * Peripheral Clock Disable Macros
 */
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




/** Peripheral Headers **/
#include "stm32f407xx_gpio_driver.h"





#endif /* INC_STM32F407XX_H_ */
