/******************************************************************************
 *
 * Module: Timers
 *
 * File Name: timers.h
 *
 * Description: Header file for the TIMERS AVR driver
 *
 * Author: Moaz Haytham
 *
 *******************************************************************************/
#ifndef TIMERS_H_
#define TIMERS_H_

#include "std_types.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define TIMER_BIT_ENABLE		LOGIC_HIGH

/*bit positions in register TCCR1A */
#define TIMER1_WGM_BITS			3


/*bit positions in register TIMSK */
#define TIMER1_OVERFLOW_INT_BIT	2

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	NORMAL_MODE, CTC_MODE
}Timer1_Mode;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer1_Prescaler;

typedef struct {
	uint16 				initial_value;
	uint16 				compare_value; // it will be used in compare mode only.
	Timer1_Prescaler 	prescaler;
	Timer1_Mode 		mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Timer1_init		(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit		(void);
void Timer1_setCallBack	(void(*a_ptr)(void));
Timer1_ConfigType * Timer1_Instance();
void Timer0_PWM_Init	(unsigned char set_duty_cycle);

#endif /* TIMERS_H_ */
