/*
 * stm32f407_gpio_driver.c
 *
 *  Created on: Nov 11, 2020
 *      Author: Aakash
 */

#include "stm32f407xx.h"

/*
 * Peripheral Clock Enable Disable Function
 */
void GPIO_PeriClkControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}else if(pGPIOx == GPIOE)
		{
			GPIOF_PCLK_EN();
		}else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
	}else if(EnorDi == DISABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}else if(pGPIOx == GPIOE)
		{
			GPIOF_PCLK_DI();
		}else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}

	}
}

/*
 * Peripheral Initialization Function
 */
void GPIO_Init(GPIO_Handle_t pGPIOHandle)
{
	uint8_t pin = pGPIOHandle.PinConfig.pinNumber;
	//1. Mode Selection
	if(pGPIOHandle.PinConfig.PinMode <= PIN_MODE_ANALOG)
	{
		pGPIOHandle.pGPIOx->MODER &= ~(0x03 << (pin * 2));
		pGPIOHandle.pGPIOx->MODER |= pGPIOHandle.PinConfig.PinMode << (pin * 2);
	}else if(pGPIOHandle.PinConfig.PinMode > PIN_MODE_ANALOG)
	{
	//Configuring Edge Selection of Interrupt
		if(pGPIOHandle.PinConfig.PinMode == PIN_MODE_RT)
		{
			//Clearing Rising Trigger Bit
			EXTI->RTSR &= ~(1 << pin);
			//Setting Rising Trigger Bit
			EXTI->RTSR |= (1 << pin);
		}else if(pGPIOHandle.PinConfig.PinMode == PIN_MODE_FT)
		{
			//Clearing Rising Trigger Bit
			EXTI->FTSR &= ~(1 << pin);
			//Setting Rising Trigger Bit
			EXTI->FTSR |= (1 << pin);
		}else if(pGPIOHandle.PinConfig.PinMode == PIN_MODE_RFT)
		{
			//Clearing Rising Trigger Bit
			EXTI->FTSR &= ~(1 << pin);
			//Setting Rising Trigger Bit
			EXTI->FTSR |= (1 << pin);

			//Clearing Rising Trigger Bit
			EXTI->RTSR &= ~(1 << pin);
			//Setting Rising Trigger Bit
			EXTI->RTSR |= (1 << pin);
		}

	//System Configuration Register Configuration
		uint8_t temp1 = (pin / 4);
		uint8_t temp2 = ((pin % 4) * 4);

		//System Configuration Clock Enable
		SYSCFG_PCLK_EN();

		SYSCFG->EXTICR[temp1] &= ~(0x0f << temp2);
		SYSCFG->EXTICR[temp1] |= (GPIO_TO_PORTCODE(pGPIOHandle.pGPIOx) << temp2);

	//Enabling Interrupt
		EXTI->IMR |= (1 << pin);
	}



	//2. Pin Output Selection
	pGPIOHandle.pGPIOx->OTYPER |= pGPIOHandle.PinConfig.PinOType << pin;

	//3. Pin Speed Selection
	pGPIOHandle.pGPIOx->OSPEEDR |= pGPIOHandle.PinConfig.PinOSpeed << (pin * 2);

	//4. Pull up and Pull down Register Configuration
	pGPIOHandle.pGPIOx->PUPDR |= pGPIOHandle.PinConfig.PinPuPd << (pin * 2);

	//5. Alternate Function Mode Configuration
	if(pGPIOHandle.PinConfig.PinMode == PIN_MODE_ALT)
	{
		uint8_t temp1 = pGPIOHandle.PinConfig.pinNumber/8;
		uint8_t temp2 = ((pGPIOHandle.PinConfig.pinNumber%8) * 4);

		pGPIOHandle.pGPIOx->AFR[temp1] &= ~(0x0f << temp2);
		pGPIOHandle.pGPIOx->AFR[temp1] |= (pGPIOHandle.PinConfig.PinALTFn << temp2);
	}
}

/*
 * GPIO Peripheral DeInitialization Function
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{

}

/*
 * GPIO Pin Read Function
 */
uint8_t GPIO_ReadFromPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	return value = (pGPIOx->IDR >> PinNumber) & 0x01;
}

/*
 * GPIO Port Read Function
 */
uint16_t GPIO_ReadFromPort(GPIO_RegDef_t *pGPIOx)
{
	return pGPIOx->IDR;
}

/*
 * GPIO Write to Pin Function
 */
void GPIO_WriteToPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pGPIOx->ODR |= (1 << PinNumber);
	}else
	{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}

/*
 * GPIO Write to Port Function
 */
void GPIO_WriteToPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
	pGPIOx->ODR = value;
}

/*
 * GPIO Pin Toggling Function
 */
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}
