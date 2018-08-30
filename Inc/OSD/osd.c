/*
 * osd.c
 *
 *  Created on: 24 рту. 2018 у.
 *      Author: feelt
 */

#include "osd.h"
#include <usart.h>

struct sOSD_Data OSD_Data;

uint32_t serialize(struct sOSD_Data* in, uint8_t* out)
{
	float* q = (float*)out;
	*q = in->pitch;				q++;
	*q = in->yaw;				q++;
	*q = in->roll;				q++;

	*q = in->V;					q++;
	*q = in->I;					q++;
	*q = in->P;					q++;

	*q = in->altitude_bar;		q++;
	*q = in->speedKph_bar;		q++;

	*q = in->latitude;			q++;
	*q = in->longitude;			q++;
	*q = in->altitude;			q++;
	*q = in->speedKph;			q++;
	*q = in->PDOP;				q++;

	unsigned int * p = (unsigned int *)q;
	*p = in->time;				p++;

	char* c = (char*)p;
	*c = in->status;			c++;
	*c = in->NS;				c++;
	*c = in->EW;				c++;

	unsigned char* s = (unsigned char*)c;
	*s = in->satellitesNum;		s++;

	return (uint32_t)q - (uint32_t)out;
}

uint32_t deserialize(uint8_t* in, struct sOSD_Data* out)
{
	float* q = (float*)in;
	out->pitch = *q;				q++;
	out->yaw = *q;					q++;
	out->roll = *q;					q++;

	out->V = *q;					q++;
	out->I = *q;					q++;
	out->P = *q;					q++;

	out->altitude_bar = *q;			q++;
	out->speedKph_bar = *q;			q++;

	out->latitude = *q;				q++;
	out->longitude = *q;			q++;
	out->altitude = *q;				q++;
	out->speedKph = *q;				q++;
	out->PDOP = *q;					q++;

	unsigned int * p = (unsigned int *)q;
	out->time = *p;					p++;

	char* c = (char*)p;
	out->status = *c;				c++;
	out->NS = *c;					c++;
	out->EW = *c;					c++;

	unsigned char* s = (unsigned char*)c;
	out->satellitesNum = *s;		s++;

	return (uint32_t)q - (uint32_t)in;
}


uint32_t last_send;
void OSD_Send(void)
{
	if (HAL_GetTick() - last_send < 30) return;
	last_send = HAL_GetTick();

	uint8_t SOD[2] = { 0x12, 0xBC };
	uint8_t EOD[2] = { 0x34, 0xDE };


	uint8_t data[64]; //sizeof(OSD_Data)


	//uint8_t partA = (uint8_t)((value & 0xFF00) >> 8);
	//uint8_t partB = (uint8_t)(value & 0x00FF);


	uint32_t data_size = serialize(&OSD_Data, data);
	//uint32_t data_size2 = deserialize(data, &OSD_Data);


	//printf(" %u, %lu %lu %0.2fV %lu\r\n", sizeof(OSD_Data), data_size, data_size2, OSD_Data.V, HAL_GetTick());


	HAL_UART_Transmit(&huart2, SOD, 2, 50);

	HAL_UART_Transmit(&huart2, data, data_size, 5000);

	HAL_UART_Transmit(&huart2, EOD, 2, 50);
}
