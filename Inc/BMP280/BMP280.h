/*
 * BMP280.h
 *
 *  Created on: 6 èþë. 2018 ã.
 *      Author: feelt
 */

#ifndef BMP280_BMP280_H_
#define BMP280_BMP280_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "util/bmp280.h"

struct BMP280
{
	struct bmp280_dev _dev;
	struct bmp280_config _config;
	struct bmp280_uncomp_data ucomp_data;

	int32_t temp32;
	uint32_t pres32;
	uint32_t pres64;
	double temp;
	double pres;

	float F;

};

int8_t BMP280_Init(struct BMP280 *bmp, uint8_t addr);
int8_t BMP280_SetFilter(struct BMP280 *bmp, uint16_t count);
int8_t BMP280_ReadData(struct BMP280 *bmp, uint16_t count);

#ifdef __cplusplus
}
#endif

#endif /* BMP280_BMP280_H_ */
