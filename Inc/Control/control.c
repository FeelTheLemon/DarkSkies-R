/*
 * out_control.c

 *
 *  Created on: 29 θών. 2018 γ.
 *      Author: feelt
 */

#include "control.h"
#include "stm32f1xx_hal.h"
#include "util.h"



struct pwm_out EN = {&htim3, TIM_CHANNEL_1};	//Engine
struct pwm_out LA = {&htim1, TIM_CHANNEL_2};	//Left Aileron
struct pwm_out RA = {&htim1, TIM_CHANNEL_3};	//Right Aileron
struct pwm_out EL = {&htim3, TIM_CHANNEL_4};	//Elevator
struct pwm_out RD = {&htim3, TIM_CHANNEL_3};	//Rudder


void OutControl_Init(void)
{
	HAL_TIM_PWM_Start(EN.htim, EN.channel);
	HAL_TIM_PWM_Start(LA.htim, LA.channel);
	HAL_TIM_PWM_Start(RA.htim, RA.channel);
	HAL_TIM_PWM_Start(EL.htim, EL.channel);
	HAL_TIM_PWM_Start(RD.htim, RD.channel);
}

void OutControl_SetValue(struct pwm_out PWM, int32_t value)
{
	TIM_OC_InitTypeDef sConfigOC;
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	//sConfigOC.Pulse = 1500;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

	sConfigOC.Pulse = value;

	if (HAL_TIM_PWM_ConfigChannel(PWM.htim, &sConfigOC, PWM.channel) != HAL_OK)
	{
	_Error_Handler(__FILE__, __LINE__);
	}
	HAL_TIM_PWM_Start(PWM.htim, PWM.channel);
}
