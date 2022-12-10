/******************************************************************************
 *
 * Module: DCMotor
 *
 * File Name: DCMotor.c
 *
 * Description: Source file for the DCMotor
 *
 * Author: Moaz Haytham
 *
 *******************************************************************************/

#include "DCMotor.h"
#include "gpio.h"
#include "timers.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void DcMotor_Init(void)
{
	/*Set the 2 pins as output pins*/
	GPIO_setupPinDirection(MOTORR_PORT_ID, MOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTORR_PORT_ID, MOTOR_IN2_PIN_ID, PIN_OUTPUT);


	GPIO_writePin(MOTORR_PORT_ID, MOTOR_IN1_PIN_ID, OFF);
	GPIO_writePin(MOTORR_PORT_ID, MOTOR_IN2_PIN_ID, OFF);
}
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	Timer0_PWM_Init(speed);
	GPIO_writePort(MOTORR_PORT_ID, state);
}
