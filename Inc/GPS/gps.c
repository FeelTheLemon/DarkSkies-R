#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "gps.h"

#include <usart.h>

struct GPS_Data *_gps;

void gpsReadData()
{
	HAL_UART_Receive_DMA(&huart3, _gps->rx_buf, sizeof(_gps->rx_buf));
}

void GPS_Init(struct GPS_Data *gps)
{
	gps->status = 'V';
	gps->NS = 'N';
	gps->EW = 'E';
	//memset(gps->line_buf, '\0', sizeof(gps->line_buf));

	_gps = gps;

	gpsReadData();
}

/*
2 $GPRMC,101202.00,A,4840.74305,N,04426.29941,E,0.949,255.50,271216,,,A*62
------------------------------------------
2 $GPVTG,255.50,T,,M,0.949,N,1.758,K,A*35
------------------------------------------
2 $GPGGA,101202.00,4840.74305,N,04426.29941,E,1,04,19.65,100.7,M,1.9,M,,*53
------------------------------------------
2 $GPGSA,A,3,31,26,14,32,,,,,,,,,21.58,19.65,8.92*06
------------------------------------------
2 $GPGSV,4,1,14,01,39,199,,03,83,302,,06,09,326,,09,11,252,*7E
------------------------------------------
2 $GPGSV,4,2,14,11,13,199,,14,27,064,35,17,11,287,,19,12,302,*7C
------------------------------------------
2 $GPGSV,4,3,14,22,79,136,20,23,50,256,,25,10,031,,26,11,115,23*72
------------------------------------------
2 $GPGSV,4,4,14,31,45,063,38,32,02,070,18*7C
------------------------------------------
2 $GPGLL,4840.74305,N,04426.29941,E,101202.00,A,A*67
------------------------------------------

*/

float mintodec(float min) {
	float degfloat = min / 100;
	float deg = floor(degfloat);
	return (deg + (degfloat - deg) * 100 / 60);
}

void gpsParseData(char *buf)
{
	//printf("Got line: %s\r\n", buf);

	char str[strlen(buf)];
	strcpy(str, buf); str[strlen(buf) - 4] = '\0';//remove checksum

	char type[4];
	strncpy(type, str + 3, 3); type[3] = '\0';

	char * pch = strtok(str, ",");

	char *exp[50];
	uint8_t exp_size = 0;

	for (int i = 0; i < 50; ++i)
	{
		exp[i] = pch;
		pch = strtok(NULL, ",");
		if (!pch)
		{
			exp_size = i + 1;
			break;
		}
	}

	//
	if(!strcmp(type, "RMC"))
	{
		_gps->time = atoi(exp[1]); //1 Time
		_gps->status = exp[2][0];
		if (_gps->status == 'A')
		{
			_gps->latitude = mintodec(atof(exp[3]));
			_gps->NS = exp[4][0];
			_gps->longitude = mintodec(atof(exp[5]));
			_gps->EW = exp[6][0];
			//pch = exp[7]; //speed knots
			_gps->track = atof(exp[8]);
		}
		
		//data.date = strtok(NULL, ","); 
		//pch = strtok(NULL, ",");
		//char z[15] = {pch[0], pch[1], '.', pch[2], pch[3], '.', pch[4], pch[5], '\0'};
		//strcpy(data.date, z);
	}

	if(!strcmp(type, "VTG"))
	{
		if (_gps->status == 'A')
		{
			_gps->speedKph = atof(exp[7]);
		}
	}

	if(!strcmp(type, "GGA"))
	{
		if (_gps->status == 'A')
		{
			_gps->satellitesNum = atoi(exp[7]);
			_gps->altitude = atoi(exp[9]);
			_gps->gSeparation = atoi(exp[10]);
		}
	}

	if(!strcmp(type, "GSA"))
	{
		
		if (_gps->status == 'A')
		{
			_gps->PDOP = atof(exp[exp_size - 3]);
			_gps->HDOP = atof(exp[exp_size - 3]);
			_gps->VDOP = atof(exp[exp_size - 3]);
		}
	}
}

void gpsUpdateData(char *buf)
{
	char * pch = strchr(buf, '\n');

	if (pch == NULL)
	{
		strcat(_gps->line_buf, buf);
	}
	else
	{
		int loc = pch-buf + 1;

		strncat(_gps->line_buf, buf, loc);

		//printf("Line: %s\r\n", _gps->line_buf);

		gpsParseData(_gps->line_buf);

		memset(_gps->line_buf, '\0', sizeof(_gps->line_buf));

		strncpy(_gps->line_buf, buf + loc, strlen(buf) - loc);
	}
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef * huart)
{
	if (huart != &huart3) return;

	size_t bs = sizeof(_gps->rx_buf) / 2;
	memcpy(_gps->pre_buf, _gps->rx_buf, bs);

	//printf("%s", _gps->pre_buf);

	gpsUpdateData(_gps->pre_buf);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
	if (huart != &huart3) return;

	size_t bs = sizeof(_gps->rx_buf) / 2;
	memcpy(_gps->pre_buf, _gps->rx_buf + bs, bs);

	//printf("%s", _gps->pre_buf);

	gpsUpdateData(_gps->pre_buf);
}
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
	//if (huart != &huart3) return;

	memcpy(_gps->pre_buf, _gps->rx_buf, sizeof(_gps->rx_buf));
	//strcpy(_gps->pre_buf, (char *)_gps->rx_buf);

	//gpsReadData();
	//HAL_LIN_Init()


	//_gps->pre_buf[sizeof(_gps->pre_buf)] = '\0';


	printf("%s\r\n", _gps->pre_buf);
	//printf("pre_buf: %s\r\n\n", _gps->pre_buf);

	//gpsUpdateData(_gps->pre_buf);
}*/
