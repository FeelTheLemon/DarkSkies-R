/*
 * sensors.h
 *
 *  Created on: 3 èþë. 2018 ã.
 *      Author: feelt
 */
#include <stdbool.h>

#ifndef SENSORS_H_
#define SENSORS_H_

#ifdef __cplusplus
 extern "C" {
#endif

struct EAngle
{
	float pitch, yaw, roll;
};
extern struct EAngle Angles;

void Sensors_Init(void);
void Sensors_Read(void);

#ifdef __cplusplus
}
#endif

#endif /* SENSORS_H_ */
