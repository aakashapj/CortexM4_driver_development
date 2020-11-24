/*
 * stm32f407xx.h
 *
 *  Created on: Nov 11, 2020
 *      Author: Aakash
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

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





#endif /* INC_STM32F407XX_H_ */
