/*
 * radio.cpp
 *
 *  Created on: 16 èþë. 2018 ã.
 *      Author: feelt
 */


#include <Control/control.h>
#include "radio.h"
#include <spi.h>
#include "RF24/RF24.h"

RF24 radio(&hspi1);

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };

void Radio_Init(void)
{

	radio.begin();



	radio.setChannel(0x66);

	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.setCRCLength(RF24_CRC_8);

	radio.setAutoAck(false);
	//radio.enableAckPayload();                         // We will be using the Ack Payload feature, so please enable it
	//radio.setRetries(0,1);								 // Smallest time between retries, max no. of retries
	radio.setPayloadSize(5);
	//radio.enableDynamicPayloads();

	radio.openWritingPipe(pipes[1]);			//TX
	radio.openReadingPipe(1,pipes[0]);

	printf("RF channel: 0x%x\r\n", radio.getChannel());

	radio.powerUp();
	printf("Radio Init 1!\r\n");
	radio.startListening();
	//radio.writeAckPayload( 1, &ack, sizeof(ack) );  // Add an ack packet for the next time around.  This is a simple


	printf("Radio Init Done!\r\n");

	//HAL_Delay(1000);

	//radio.printDetails();														 // Dump the configuration of the rf unit for debugging

	//attachInterrupt(digitalPinToInterrupt(RF24_IRQ), check_radio, FALLING);						 // Attach interrupt handler to interrupt #0 (using pin 2) on BOTH the sender and receiver
	//attachInterrupt(RF24_IRQ, check_radio, FALLING);
}

void Radio_Read(void)
{
	//if (radio.available()) {
		// Read in the data
		uint8_t data[5];
		radio.read(data, sizeof(data));

		int8_t lx = data[0];
		int8_t ly = data[1];
		int8_t rx = data[2];
		int8_t ry = data[3];
		uint8_t th = data[4];

		//printf("lx: %.2f, ly: %.2f, rx: %.2f, ry: %.2f, th: %.2f \r\n", lx, ly, rx, ry, th);
		//printf("lx: %i, ly: %i, rx: %i, ry: %i, th: %u \r\n", lx, ly, rx, ry, th);

		/*if (th < 20)
			OutControl_SetValue(EN, 1300);
		else
			OutControl_SetValue(EN, map(th, 10, 255, 1800, 2450));*/

		OutControl_SetValue(EN, map(th, 0, 255, SERVO_MIN, SERVO_MAX));

		UNUSED(ry);

		OutControl_SetValue(LA, map(lx, -128, 127, SERVO_MIN, SERVO_MAX));
		OutControl_SetValue(RA, map(lx, -128, 127, SERVO_MIN, SERVO_MAX));
		OutControl_SetValue(EL, map(ly, -128, 127, SERVO_MAX, SERVO_MIN));
		OutControl_SetValue(RD, map(rx, -128, 127, SERVO_MAX, SERVO_MIN));

		//Serial3.print(F("Got payload "));
		//Serial3.println(data[5]);

	//}
}


void Radio_Interrupt(void)
{
	bool tx, fail, rx;
	radio.whatHappened(tx, fail, rx);

	//if (tx)
		//Serial3.println(F("Ack Payload:Sent"));

	//if (fail)
		//Serial3.println(F("Ack Payload:Failed"));

	if ( rx || radio.available()) {
		Radio_Read();
	}
}


