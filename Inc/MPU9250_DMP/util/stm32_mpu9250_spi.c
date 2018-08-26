/******************************************************************************
arduino_mpu9250_i2c.cpp - MPU-9250 Digital Motion Processor Arduino Library 
Jim Lindblom @ SparkFun Electronics
original creation date: November 23, 2016
https://github.com/sparkfun/SparkFun_MPU9250_DMP_Arduino_Library

This library implements motion processing functions of Invensense's MPU-9250.
It is based on their Emedded MotionDriver 6.12 library.
	https://www.invensense.com/developers/software-downloads/

Development environment specifics:
Arduino IDE 1.6.12
SparkFun 9DoF Razor IMU M0

Supported Platforms:
- ATSAMD21 (Arduino Zero, SparkFun SAMD21 Breakouts)
******************************************************************************/
#include <spi.h>
#include "stm32_mpu9250_spi.h"
#include <MPU9250_DMP/MPU9250_RegisterMap.h>

#define READ_FLAG   0x80

int stm32_spi_write_slave(unsigned char slave_addr, unsigned char reg_addr,
        unsigned char length, unsigned char * data)
{
	while (length > 0)
	{
		uint8_t tx;

		tx = slave_addr;
		if (stm32_spi_write(0x00, MPU9250_I2C_SLV0_ADDR, 1, &tx))
			return -1;

		if (stm32_spi_write(0x00, MPU9250_I2C_SLV0_REG, 1, &reg_addr))
			return -1;

		if (stm32_spi_write(0x00, MPU9250_I2C_SLV0_DO, 1, data++))
			return -1;

		tx = 0x80 | 1;
		if (stm32_spi_write(0x00, MPU9250_I2C_SLV0_CTRL, 1, &tx))
			return -1;

		length--;
	}


	return 0;
}

int stm32_spi_read_slave(unsigned char slave_addr, unsigned char reg_addr,
        unsigned char length, unsigned char * data)
{
	uint8_t tx;

	tx = 0x80 | slave_addr;
	if (stm32_spi_write(0x00, MPU9250_I2C_SLV0_ADDR, 1, &tx))
		return -1;

	if (stm32_spi_write(0x00, MPU9250_I2C_SLV0_REG, 1, &reg_addr))
		return -1;

	tx = 0x80 | length;
	if (stm32_spi_write(0x00, MPU9250_I2C_SLV0_CTRL, 1, &tx))
		return -1;

	HAL_Delay(1);

	if (stm32_spi_read(0x00, MPU9250_EXT_SENS_DATA_00, length, data))
		return -1;

	return 0;
}

int stm32_spi_write(unsigned char slave_addr, unsigned char reg_addr,
                       unsigned char length, unsigned char * data)
{
	if (slave_addr != 0x00 && slave_addr != 0x68 && slave_addr != 0x69)
		return stm32_spi_write_slave(slave_addr, reg_addr, length, data);

	HAL_StatusTypeDef status;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

	status = HAL_SPI_Transmit(&hspi2, &reg_addr, 1, 50);
	status = HAL_SPI_Transmit(&hspi2, data, (uint16_t)length, 50);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

	if (status != HAL_OK) printf("stm32_spi_write FAILED with status 0x%x, error: 0x%lx , state: 0x%x, reg: 0x%x\r\n", status, HAL_SPI_GetError(&hspi2), HAL_SPI_GetState(&hspi2), reg_addr);
	return status;
}

int stm32_spi_read(unsigned char slave_addr, unsigned char reg_addr,
                       unsigned char length, unsigned char * data)
{
	if (slave_addr != 0x00 && slave_addr != 0x68 && slave_addr != 0x69)
		return stm32_spi_read_slave(slave_addr, reg_addr, length, data);

	HAL_StatusTypeDef status;

	reg_addr |= READ_FLAG;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

	status = HAL_SPI_Transmit(&hspi2, &reg_addr, 1, 50);
	status = HAL_SPI_Receive(&hspi2, data, (uint16_t)length, 50);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

	if (status != HAL_OK) printf("stm32_spi_read FAILED with status 0x%x, error: 0x%lx , state: 0x%x, reg: 0x%x\r\n", status, HAL_SPI_GetError(&hspi2), HAL_SPI_GetState(&hspi2), reg_addr ^ READ_FLAG);
	return status;
}
