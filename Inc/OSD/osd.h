/*
 * osd.h
 *
 *  Created on: 24 рту. 2018 у.
 *      Author: feelt
 */

#ifndef OSD_H_
#define OSD_H_

void OSD_Send(void);

struct OSD_Data
{
	float pitch;
	float yaw;
	float roll;
};

#endif /* OSD_H_ */
