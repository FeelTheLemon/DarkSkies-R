/*
 * sensors.c
 *
 *  Created on: 3 июл. 2018 г.
 *      Author: feelt
 */
#include "sensors.h"
#include "i2c.h"
#ifdef HAL_IWDG_MODULE_ENABLED
#include "iwdg.h"
#endif
#include <math.h>
#include <string.h>
#include <util.h>
#include <MPU9250_DMP/MPU9250_DMP.h>
#include <BMP280/BMP280.h>
#include <GPS/gps.h>

#include <MPU9250_DMP/util/stm32_mpu9250_spi.h>
#include <MPU9250_DMP/MPU9250_RegisterMap.h>

struct EAngle Angles;

MPU9250_DMP mpu9250;

struct BMP280 BMP_F;
struct BMP280 BMP_B;
struct GPS_Data GPS;

uint32_t c = 0;

void scan_i2c(void)
{
	printf("Scanning I2C bus:\r\n");
	HAL_StatusTypeDef result;
	uint8_t i;

	printf("## *0 *1 *2 *3 *4 *5 *6 *7 *8 *9 *a *b *c *d *e *f\r\n0* ");

	for (i=0; i<128; i++)
	{
		/*
		* the HAL wants a left aligned i2c address
		* &hi2c1 is the handle
		* (uint16_t)(i<<1) is the i2c address left aligned
		* retries 2
		* timeout 2
		*/
		result = HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)(i<<1), 2, 2);
		if (result != HAL_OK) // HAL_ERROR or HAL_BUSY or HAL_TIMEOUT
		{
			printf(".  "); // No ACK received at that address
			//printf("%.2x ", i);
		}
		if (result == HAL_OK)
		{
			printf("%.2x ", i); // Received an ACK at that address
		}

		if ((i+1) % 16 == 0 && i < 127) // HAL_ERROR or HAL_BUSY or HAL_TIMEOUT
		{
			printf("\r\n%x* ", (i+1) % 0xf); // No ACK received at that address
		}

		#ifdef HAL_IWDG_MODULE_ENABLED
		HAL_IWDG_Refresh(&hiwdg);
		#endif
	}
	printf("\r\n\n");
}


void Sensors_Init(void)
{

	scan_i2c();

	mpu9250.begin();

	mpu9250.dmpBegin(DMP_FEATURE_6X_LP_QUAT | // Enable 6-axis quat
				   DMP_FEATURE_GYRO_CAL, // Use gyro calibration
				  10); // Set DMP FIFO rate to 10 Hz
	  // DMP_FEATURE_LP_QUAT can also be used. It uses the
	  // accelerometer in low-power mode to estimate quat's.
	  // DMP_FEATURE_LP_QUAT and 6X_LP_QUAT are mutually exclusive

	#ifdef HAL_IWDG_MODULE_ENABLED
	HAL_IWDG_Refresh(&hiwdg);
	#endif

	BMP280_Init(&BMP_B, BMP280_I2C_ADDR_PRIM);
	BMP280_Init(&BMP_F, BMP280_I2C_ADDR_SEC);

	#ifdef HAL_IWDG_MODULE_ENABLED
	HAL_IWDG_Refresh(&hiwdg);
	#endif

	GPS_Init(&GPS);

}

void Sensors_Read(void)
{
	// Check for new data in the FIFO
	if ( mpu9250.fifoAvailable() )
	{
		// Use dmpUpdateFifo to update the ax, gx, mx, etc. values
		if ( mpu9250.dmpUpdateFifo() == INV_SUCCESS)
		{
			// computeEulerAngles can be used -- after updating the
			// quaternion values -- to estimate roll, pitch, and yaw
			mpu9250.computeEulerAngles();

			//printf("p: %.2f, y: %.2f, r: %.2f \r\n", mpu9250.pitch, mpu9250.yaw, mpu9250.roll);
		}
	}


	if (c % 5 == 0)
	{
		BMP280_ReadData(&BMP_F, 1);
		BMP280_ReadData(&BMP_B, 1);

		float fp = BMP_F.pres + 34;
		float bp = BMP_B.pres;

		float p = 1.2; //плотность воздуха

		double v = sqrt((2 * (fp - bp)) / (1.0f * p));

		UNUSED(v);
		//printf("pres: f: %f, b:%f speed: %f \r\n", fp, bp, v * 3.6);

	}

	if (c % 20 == 0)
	{
		//printf("GPS: status: %c, time: %u, %f%c, %f%c\r\n", GPS.status, GPS.time, GPS.latitude, GPS.NS, GPS.longitude, GPS.EW);
	}
	c++;
}

