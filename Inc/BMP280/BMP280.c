/*
 * BMP280.c
 *
 *  Created on: 6 èşë. 2018 ã.
 *      Author: feelt
 */

#include "BMP280.h"
#include <i2c.h>

int8_t i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
	HAL_StatusTypeDef status;

	//status = HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)dev_id << 1, &reg_addr, 1, 1000);
	//status = HAL_I2C_Master_Receive(&hi2c1, (uint16_t)dev_id << 1, data, (uint16_t)len, 1000);

	status = HAL_I2C_Mem_Read(&hi2c1, (uint16_t)dev_id << 1, (uint16_t)reg_addr, I2C_MEMADD_SIZE_8BIT, data, (uint16_t)len, 50);

	if (status != HAL_OK) { printf("HAL_I2C_Mem_Read (s) FAILED with status 0x%x, dev: 0x%x, reg: 0x%x\r\n", status, dev_id, reg_addr); }

	return status;
}


int8_t i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Write(&hi2c1, (uint16_t)dev_id << 1, (uint16_t)reg_addr, I2C_MEMADD_SIZE_8BIT, data, (uint16_t)len, 50);

	if (status != HAL_OK) { printf("HAL_I2C_Mem_Write FAILED with status 0x%x, dev: 0x%x, reg: 0x%x\r\n", status, dev_id, reg_addr); }

	return status;
}


int8_t BMP280_Init(struct BMP280 *bmp, uint8_t addr)
{
	bmp->F = 1.0f;
	int8_t rslt;

	/* Sensor interface over I2C with primary slave address  */
	bmp->_dev.dev_id = addr;//BMP280_I2C_ADDR_PRIM; //BMP280_I2C_ADDR_SEC
	bmp->_dev.intf = BMP280_I2C_INTF;
	bmp->_dev.read = i2c_read;
	bmp->_dev.write = i2c_write;
	bmp->_dev.delay_ms = HAL_Delay;

	rslt = bmp280_init(&bmp->_dev);
	if (rslt != BMP280_OK)
		printf("bmp280_init failed with result 0x%x\r\n", rslt);

	/* Always read the current settings before writing, especially when
	 * all the configuration is not modified
	 */
	rslt = bmp280_get_config(&bmp->_config, &bmp->_dev);
	if (rslt != BMP280_OK)
		printf("bmp280_get_config failed with result 0x%x\r\n", rslt);

	/* Overwrite the desired settings */
	bmp->_config.filter = BMP280_FILTER_COEFF_16;
	bmp->_config.os_pres = BMP280_OS_16X;
	bmp->_config.os_temp = BMP280_OS_4X;
	bmp->_config.odr = BMP280_ODR_0_5_MS;

	rslt = bmp280_set_config(&bmp->_config, &bmp->_dev);
	if (rslt != BMP280_OK)
		printf("bmp280_set_config failed with result 0x%x\r\n", rslt);

	/* Always set the power mode after setting the configuration */
	rslt = bmp280_set_power_mode(BMP280_NORMAL_MODE, &bmp->_dev);
	if (rslt != BMP280_OK)
		printf("bmp280_set_power_mode failed with result 0x%x\r\n", rslt);

	return rslt;
}

int8_t BMP280_ReadData(struct BMP280 *bmp, uint16_t count)
{
	int8_t rslt = 0;

	uint8_t meas_dur = bmp280_compute_meas_time(&bmp->_dev);

	//printf("Measurement duration: %dms\r\n", meas_dur);

	/* Loop to read out 10 samples of data */
	for (uint8_t i = 0; (i < count) && (rslt == BMP280_OK); i++) {
	    bmp->_dev.delay_ms(meas_dur); /* Measurement time */

	    rslt = bmp280_get_uncomp_data(&bmp->ucomp_data, &bmp->_dev);
	    if (rslt != BMP280_OK)
			printf("bmp280_get_uncomp_data failed with result 0x%x\r\n", rslt);

	    bmp->temp32 = bmp280_comp_temp_32bit(bmp->ucomp_data.uncomp_temp, &bmp->_dev);
	    bmp->pres32 = bmp280_comp_pres_32bit(bmp->ucomp_data.uncomp_press, &bmp->_dev);
	    bmp->pres64 = bmp280_comp_pres_64bit(bmp->ucomp_data.uncomp_press, &bmp->_dev);
	    bmp->temp = bmp280_comp_temp_double(bmp->ucomp_data.uncomp_temp, &bmp->_dev);
	    bmp->pres = bmp280_comp_pres_double(bmp->ucomp_data.uncomp_press, &bmp->_dev);

	    //bmp->_dev.delay_ms(1);
	}

	return rslt;
}
