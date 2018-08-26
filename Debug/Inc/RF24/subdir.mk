################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Inc/RF24/RF24.cpp 

OBJS += \
./Inc/RF24/RF24.o 

CPP_DEPS += \
./Inc/RF24/RF24.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/RF24/%.o: ../Inc/RF24/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"D:/Documents/STM32SW/DarkSkies-R/Inc" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/Ac6/SystemWorkbench/plugins/fr.ac6.mcu.externaltools.arm-none.win32_1.16.0.201807130628/tools/compiler/arm-none-eabi/include" -I"C:/Ac6/SystemWorkbench/plugins/fr.ac6.mcu.externaltools.arm-none.win32_1.16.0.201807130628/tools/compiler/arm-none-eabi/include/c++/7.2.1" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


