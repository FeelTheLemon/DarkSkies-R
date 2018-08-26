################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/GPS/gps.c 

OBJS += \
./Inc/GPS/gps.o 

C_DEPS += \
./Inc/GPS/gps.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/GPS/%.o: ../Inc/GPS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"D:/Documents/STM32SW/DarkSkies-R/Inc" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


