################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/Src/stm32f407_gpio_driver.c 

OBJS += \
./driver/Src/stm32f407_gpio_driver.o 

C_DEPS += \
./driver/Src/stm32f407_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
driver/Src/stm32f407_gpio_driver.o: ../driver/Src/stm32f407_gpio_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -c -I../Inc -I"F:/Embedded Pojects/CortexM4_driver_development/STM32F407_Driver_Development/driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"driver/Src/stm32f407_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

