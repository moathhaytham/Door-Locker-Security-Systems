/******************************************************************************
 *
 * Module: Timers
 *
 * File Name: timers.c
 *
 * Description: Source file for the TIMERS AVR driver
 *
 * Author: Moaz Haytham
 *
 *******************************************************************************/
#include "timers.h"
#include "avr/io.h"
#include <avr/interrupt.h>
#include "common_macros.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*Since Atmega32 has 3 timers, instances of Timer0 and Timer1 are made to avoid overlapping usages of a single timer at once*/
static Timer1_ConfigType Timer1 = {0,0,NO_CLOCK, NORMAL_MODE};


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	switch(Config_Ptr ->mode)
	{
	case NORMAL_MODE:

		/*Clear Register first then set the normal mode and prescalar*/
		TCCR1A = 0;
		TCCR1A = (TIMER_BIT_ENABLE<<FOC1A) | (TIMER_BIT_ENABLE<<FOC1B);

		/*Clear Register first then set the normal mode and prescalar*/
		TCCR1B = 0;
		TCCR1B = (Config_Ptr->mode << TIMER1_WGM_BITS) | (Config_Ptr->prescaler);

		/* Initial Value for Timer1 */
		TCNT1 = 0;

		TIMSK = (TIMER_BIT_ENABLE << TIMER1_OVERFLOW_INT_BIT);
		break;


	case CTC_MODE:
		/*Clear Register first then set the normal mode and prescalar*/
		TCCR1A = 0;
		TCCR1A = (TIMER_BIT_ENABLE<<FOC1A) | (TIMER_BIT_ENABLE<<FOC1B) ;

		/*Clear Register first then set the normal mode and prescalar*/
		TCCR1B = 0;
		TCCR1B = (Config_Ptr->mode << TIMER1_WGM_BITS) | (Config_Ptr->prescaler);

		/* Initial Value for Timer1 */
		TCNT1 = 0;

		OCR1A = Config_Ptr->compare_value;

		TIMSK = (TIMER_BIT_ENABLE << TIMER1_OVERFLOW_INT_BIT);
		break;

	}

	SREG|= (1<<7);
}


void Timer1_deInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;

	TCNT1 = 0;
	OCR1A = 0;

	TIMSK = 0xC3;
}


void Timer1_setCallBack	(void(*a_ptr)(void))
{
	/* Global variables to hold the address of the call back function in the application */
	static volatile void (*g_callBackPtr)(void) = NULL_PTR;
}

Timer1_ConfigType * Timer1_Instance()
{
	return &Timer1;
}


void Timer0_PWM_Init(unsigned char set_duty_cycle)
{

	TCNT0 = 0; //Set Timer Initial value

	OCR0  = (set_duty_cycle * 255)/ 100; // Set Compare Value

	DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */

	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

	if(set_duty_cycle == 0)
		CLEAR_BIT(TCCR0,CS01);
}
