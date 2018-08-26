/*
 * out_control.h
 *
 *  Created on: 29 θών. 2018 γ.
 *      Author: feelt
 */


#ifndef OUT_CONTROL_H_
#define OUT_CONTROL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "tim.h"

struct pwm_out
{
	TIM_HandleTypeDef *htim;
	unsigned int channel;
};

extern struct pwm_out EN;	//Engine
extern struct pwm_out LA;	//Left Aileron
extern struct pwm_out RA;	//Right Aileron
extern struct pwm_out EL;	//Elevator
extern struct pwm_out RD;	//Rudder

void OutControl_Init(void);
void OutControl_SetValue(struct pwm_out PWM, int32_t value);

#define SERVO_MAX	2450//2350
#define SERVO_MIN	625//950
#define SERVO_MID	1580

#ifdef __cplusplus
}
#endif

#endif /* OUT_CONTROL_H_ */
