/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Moaz Haytham
 *
 *******************************************************************************/


#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*This #define is used to set bits for Flags, Interrupts, Condition Detection(such as Frame Error, Data Overrun Error)
 * in the Control and Status Registers
 * */
#define UART_BIT_SETTER						LOGIC_HIGH


/* UCSRA bit numbers*/
#define UART_RECEIVE_FLAG_BIT_NUMBER		7
#define UART_TRANSMIT_FLAG_BIT_NUMBER		6
#define UART_DATA_REGISTER_EMPTY_FLAG_BIT_NUMBER	5
#define UART_FRAME_ERROR_FLAG_BIT_NUMBER	4
#define UART_DATA_OVERRUN_FLAG_BIT_NUMBER	3
#define UART_2X_TRANS_SPEED_BIT_NUMBER		1

/* UCSRB bit numbers*/
#define UART_RECEIVE_COMPLETE_INTERRUPT_ENABLE_BIT_NUMBER		7
#define UART_TRANSMIT_COMPLETE_INTERRUPT_ENABLE_BIT_NUMBER		6
#define UART_DATAREG_EMPTY_INTERRUPT_ENABLE_BIT_NUMBER			5
#define UART_RECEIVER_ENABLE_BIT_NUMBER							4
#define UART_TRANSMITTER_ENABLE_BIT_NUMBER						3


/* UCSRC bit numbers*/
#define UART_REGISTER_SELECT_BIT_NUMBER							7
#define UART_MODE_SELECT_BIT_NUMBER								6
#define UART_PARITY_MODE_BIT_SHIFTER							4
#define UART_STOP_BIT_SELECT_BIT_NUMBER							3
#define UART_CHAR_SIZE_BIT_SHIFTER								1



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef uint8 UART_BitData;


typedef enum{

	PARITY_DISABLED, PARITY_RESERVED, PARITY_EVEN, PARITY_ODD
}UART_Parity;

typedef enum{
	ONE_STOP_BIT, TWO_STOP_BITS
}UART_StopBit;


typedef enum{
	BAUDRATE_10, BAUDRATE_300, BAUDRATE_600, BAUDRATE_1200, BAUDRATE_2400, BAUDRATE_4800, BAUDRATE_9600,\
	BAUDRATE_14400, BAUDRATE_19200, BAUDRATE_38400, BAUDRATE_57600, BAUDRATE_115200, BAUDRATE_128000, \
	BAUDRATE_256000
}UART_BaudRate;

typedef enum{
	FIVE_BIT_CHAR, SIX_BIT_CHAR, SEVEN_BIT_CHAR, EIGHT_BIT_CHAR, RES1, RES2, RES3, NINE_BIT_CHAR
}UART_CharSize;

typedef struct{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;


typedef enum {
	Asynchronous, Synchronous
}UART_ModeSelect;


typedef enum{
	RISING_EDGE, FALLING_EDGE
}UART_ClkPolarity;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init( UART_ConfigType * const Config_Ptr );

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
