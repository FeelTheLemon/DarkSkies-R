#ifndef GPS_H_
#define GPS_H_
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif


struct satellite {
	unsigned int id;
	float elevation;
	float azimuth;
	float SNR;
};

struct GPS_Data {
	unsigned int time;
	char status;
	float latitude;
	char NS;
	float longitude;
	char EW;
	float track;
	char date[15];
	float speedKph;
	unsigned char satellitesNum;
	float altitude;
	float gSeparation;
	float PDOP;
	float HDOP;
	float VDOP;

	uint8_t rx_buf[16];
	char pre_buf[10];
	char line_buf[128];
};

void GPS_Init(struct GPS_Data *data);

#ifdef __cplusplus
}
#endif

#endif
