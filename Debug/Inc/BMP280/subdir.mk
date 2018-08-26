################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/BMP280/BMP280.c 

OBJS += \
./Inc/BMP280/BMP280.o 

C_DEPS += \
./Inc/BMP280/BMP280.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/BMP280/%.o: ../Inc/BMP280/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"D:/Documents/STM32SW/DarkSkies-R/Inc" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


