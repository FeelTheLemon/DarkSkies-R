/*
 * osd.h
 *
 *  Created on: 24 рту. 2018 у.
 *      Author: feelt
 */

#ifndef OSD_H_
#define OSD_H_

#include <stdint.h>

void OSD_Send(void);
void OSD_UartReady(void);

struct sOSD_Data
{
	float pitch, yaw, roll;

	float V, I, P;

	float altitude_bar, speedKph_bar;

	float latitude, longitude, altitude, speedKph, PDOP;
	unsigned int time;
	char status, NS, EW;
	unsigned char satellitesNum;
};
extern struct sOSD_Data OSD_Data;

#endif /* OSD_H_ */
