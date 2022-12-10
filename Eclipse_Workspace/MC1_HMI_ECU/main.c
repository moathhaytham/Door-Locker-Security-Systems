#include"lcd.h"
#include "uart.h"
#include "keypad.h"
#include <util/delay.h>

#define VALID_PASSWORD_LENGTH		5
#define ENTER_BUTTON 		'='
#define UART_STOPPING_CONDITION		'#'

UART_ConfigType g_uartConfiguration = { 0, PARITY_DISABLED, ONE_STOP_BIT, BAUDRATE_9600};

uint8 g_password[6];
uint8 g_charIndex = 0;

typedef enum{
	CREATE_PASSWORD_STATE, REENTERING_PASSWORD
}State;

typedef enum{
	DOOR_OPENED, DOOR_CLOSED
}Door_State;

typedef struct{
	State currentState ;
	State previousState;
	char trialNumber;
	Door_State doorState;
}App_State;


int main(void)
{
	unsigned char key;

	App_State currentState = OBTAINING_INPUT;

	/*Initializing modules needed*/

	LCD_init();

	UART_init(&g_uartConfiguration);
	/*End of Initialization section*/

	_delay_ms(500);


	/* Display message for the user + moving the cursor to the second row*/
	LCD_displayString("Plz Enter Pass:");
	LCD_moveCursor(1,0);

	/*The while loop will keep checking for input from the user until enter button is pressed*/
	while(1)
	{
//		switch(currentState)
//		{
//		case OBTAINING_INPUT:
			/* Get the pressed key number, if any switch pressed for more than 500 ms it will considered more than one press */
			key = KEYPAD_getPressedKey();

			if( ( VALID_PASSWORD_LENGTH >  g_charIndex)  &&  (key <= 9) && (key >= 0))
			{
				/*Store the pressed key in the array and increment the index*/
				g_password[g_charIndex++] = key;

				//			LCD_intgerToString(key);   /* display the pressed keypad switch */
				LCD_displayCharacter('*'); /* display an asterisk on the screen*/

			}

			/*In case the user pressed the enter button
			 * --> have to check if password is valid(5 numbers)
			 * --> in case the password is invalid, user must still enter a valid
			 * */
			else if( ( VALID_PASSWORD_LENGTH <=  g_charIndex) && (ENTER_BUTTON == key) )
			{
				/*add the stopping condition in the last index*/
				g_password[5] = UART_STOPPING_CONDITION;

				UART_sendString(g_password);
			}

			//		else
			//		{
			//			/*Ignore other key presses*/
			////			LCD_displayCharacter(key); /* display the pressed keypad switch */
			////			LCD_displayCharacter('*');
			//		}


			_delay_ms(500); /* Press time */
			break;

		case REENTERING_PASSWORD:

//		}
	break;
	}

}
