/*
 * main.c
 *
 *  Created on: Nov 9, 2022
 *      Author: moath
 */


#include "uart.h"
#include "lcd.h"
#include <util/delay.h>

UART_ConfigType g_uartConfiguration = { 0, PARITY_DISABLED, ONE_STOP_BIT, BAUDRATE_9600};

uint8 g_password[6];
uint8 g_charIndex = 0;

int main(void)
{
	unsigned char key;

	/*Initializing modules needed*/

	LCD_init();

	UART_init(&g_uartConfiguration);
	/*End of Initialization section*/

	_delay_ms(500);

	LCD_displayString("Password is:");
	LCD_moveCursor(1,0);

	while(1)
	{

		/* Receive String from MC1 through UART */
		UART_receiveString(g_password);

		/* Display the received string on the LCD display */
		LCD_intgerToString(g_password[1]);


//		g_charIndex = UART_recieveByte();
//		LCD_intgerToString(g_charIndex);
	}

}
