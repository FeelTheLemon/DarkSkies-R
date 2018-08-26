################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/MPU9250_DMP/util/inv_mpu.c \
../Inc/MPU9250_DMP/util/inv_mpu_dmp_motion_driver.c \
../Inc/MPU9250_DMP/util/stm32_mpu9250_clk.c \
../Inc/MPU9250_DMP/util/stm32_mpu9250_spi.c 

OBJS += \
./Inc/MPU9250_DMP/util/inv_mpu.o \
./Inc/MPU9250_DMP/util/inv_mpu_dmp_motion_driver.o \
./Inc/MPU9250_DMP/util/stm32_mpu9250_clk.o \
./Inc/MPU9250_DMP/util/stm32_mpu9250_spi.o 

C_DEPS += \
./Inc/MPU9250_DMP/util/inv_mpu.d \
./Inc/MPU9250_DMP/util/inv_mpu_dmp_motion_driver.d \
./Inc/MPU9250_DMP/util/stm32_mpu9250_clk.d \
./Inc/MPU9250_DMP/util/stm32_mpu9250_spi.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/MPU9250_DMP/util/%.o: ../Inc/MPU9250_DMP/util/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"D:/Documents/STM32SW/DarkSkies-R/Inc" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/Documents/STM32SW/DarkSkies-R/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


