/*
 * radio.h
 *
 *  Created on: 16 èþë. 2018 ã.
 *      Author: feelt
 */

#ifndef RADIO_H_
#define RADIO_H_

#ifdef __cplusplus
 extern "C" {
#endif

void Radio_Init(void);
void Radio_Read(void);
void Radio_Interrupt(void);

#ifdef __cplusplus
}
#endif

#endif /* RADIO_H_ */
