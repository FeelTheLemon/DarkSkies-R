/*
 * sensors.h
 *
 *  Created on: 3 èþë. 2018 ã.
 *      Author: feelt
 */
#include <stdbool.h>
#include <GPS/gps.h>

#ifndef SENSORS_H_
#define SENSORS_H_

#ifdef __cplusplus
 extern "C" {
#endif

struct sAngle
{
	float pitch, yaw, roll;
};
extern struct sAngle Angles;

struct sPower
{
	float V;
	float A;
	float P;
};
extern struct sPower Power;
extern struct GPS_Data GPS;

void Sensors_Init(void);
void Sensors_Read(void);

#ifdef __cplusplus
}
#endif

#endif /* SENSORS_H_ */
