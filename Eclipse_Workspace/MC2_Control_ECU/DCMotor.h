 /******************************************************************************
 *
 * Module: DCMotor
 *
 * File Name: DCMotor.h
 *
 * Description: Header file for the DCMotor
 *
 * Author: Moaz Haytham
 *
 *******************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define MOTORR_PORT_ID		PORTB_ID

#define MOTOR_IN1_PIN_ID	PIN0_ID
#define MOTOR_IN2_PIN_ID	PIN1_ID
//#define MOTOR_EN_PIN_ID		PIN2_ID


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	OFF,CW,ANTI_CW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Function that initiates the motor by setting the direction of the 2 motor pins as output pins
 */
void DcMotor_Init(void);

/*
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor
 * based on the state input state value.
 *
 * It sends the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
