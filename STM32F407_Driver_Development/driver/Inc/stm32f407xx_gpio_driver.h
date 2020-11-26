/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Nov 11, 2020
 *      Author: Aakash
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

//#include "stm32f407xx.h"

typedef struct
{
	uint8_t pinNumber;
	uint8_t PinMode;
	uint8_t PinOType;
	uint8_t PinOSpeed;
	uint8_t PinPuPd;

}GPIO_PinConfig_t;

typedef struct
{
	GPIO_PinConfig_t PinConfig;
	GPIO_RegDef_t *pGPIOx;
}GPIO_Handle_t;


/*
 * GPIO Pin Configuration Macros
 */

#define PIN_MODE_IN			0
#define PIN_MODE_OUT		1
#define PIN_MODE_ALT	 	2
#define PIN_MODE_ANALOG 	3

#define PIN_OTYPE_PP		0
#define PIN_OTYPE_OD		1

#define PIN_OSPEED_LOW		0
#define PIN_OSPEED_MED		1
#define PIN_OSPEED_HIGH		2
#define PIN_OSPEED_FAST		3

#define PIN_PUPD_NONE		0
#define PIN_PUPD_PU			1
#define PIN_PUPD_PD			2

#define PIN_ALTFN_0			0
#define PIN_ALTFN_1			1
#define PIN_ALTFN_2			2
#define PIN_ALTFN_3			3
#define PIN_ALTFN_4			4
#define PIN_ALTFN_5			5
#define PIN_ALTFN_6			6
#define PIN_ALTFN_7			7
#define PIN_ALTFN_8			8
#define PIN_ALTFN_9			9
#define PIN_ALTFN_10		10
#define PIN_ALTFN_11		11
#define PIN_ALTFN_12		12
#define PIN_ALTFN_13		13
#define PIN_ALTFN_14		14
#define PIN_ALTFN_15		15

/*
 * Function Prototype of Driver file
 */
void GPIO_PeriClkControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);
void GPIO_Init(GPIO_Handle_t pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);
void GPIO_ReadFromPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
void GPIO_ReadFromPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t EnorDi);
void GPIO_WriteToPort(GPIO_RegDef_t *pGPIOx, uint16_t value);
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
