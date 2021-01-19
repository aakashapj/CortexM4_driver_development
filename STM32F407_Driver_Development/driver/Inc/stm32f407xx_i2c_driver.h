/*
 * stm32f407xx_i2c_driver.h
 *
 *  Created on: Jan 16, 2021
 *      Author: Aakash
 */

#ifndef INC_STM32F407XX_I2C_DRIVER_H_
#define INC_STM32F407XX_I2C_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint32_t I2C_SCLSpeed;
	uint8_t	I2C_ACKControl;
	uint8_t I2C_FMDutyCycle;
	uint8_t I2C_DeviceAddress;
}I2C_Config_t;

typedef struct
{
	I2C_Config_t I2C_PinConfig;
	I2C_RegDef_t *pI2C;
}I2C_Handle_t;


/* Acknowledge Enable Control */
#define I2C_ACKCONTROL_EN		1
#define I2C_ACKCONTROL_DI		0

/* Serial Clock Speed*/
#define I2C_SCLSPEED_SM			100000
#define I2C_SCLSPEED_FM_4K		400000

/* Fast Mode Duty Cycle*/
#define I2C_FM_DUTY_2			0
#define I2C_FM_DUTY_16_9		1

/* I2C Bit Definition Macros */

/* I2C Status Register 1 Macros */
#define I2C_SR1_SB			0
#define I2C_SR1_ADDR		1
#define I2C_SR1_BTF			2
#define I2C_SR1_ADDR10		3
#define I2C_SR1_STOPF		4
#define I2C_SR1_RxNE		6
#define I2C_SR1_TxE			7
#define I2C_SR1_BERR		8
#define I2C_SR1_ARLO		9
#define I2C_SR1_AF			10
#define I2C_SR1_OVR			11
#define I2C_SR1_PECERR		12
#define I2C_SR1_TIMEOUT		14
#define I2C_SR1_SMBALERT	15

/* I2C Status Register 2 Macros */
#define I2C_SR2_MSL			0
#define I2C_SR2_BUSY		1
#define I2C_SR2_TRA			2
#define I2C_SR2_GENCALL		4
#define I2C_SR2_SMBFAULT	5
#define I2C_SR2_SMBHOST		6
#define I2C_SR2_DUALF		7
#define I2C_SR2_PEC			8

/* I2C Function Prototype */
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_Handle_t *pI2CHandle);
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t *SlaveAddr, uint8_t Sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t *SlaveAddr, uint8_t Sr);


#endif /* INC_STM32F407XX_I2C_DRIVER_H_ */
