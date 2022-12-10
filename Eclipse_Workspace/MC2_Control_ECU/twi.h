/******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 * Author: Moaz Haytham
 *
 *******************************************************************************/ 

#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


/* I2C Control Register TWCR Bit Numbers*/
#define TWI_INT_FLAG		7
#define TWI_ENABLE_ACK_BIT	6
#define TWI_START_COND_BIT	5
#define TWI_STOP_COND_BIT	4
#define TWI_W_COND_FLAG		3
#define TWI_ENABLE_BIT		2
#define TWI_INT_ENABLE		0


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	PRESCALE_VALUE_1, PRESCALE_VALUE_4, PRESCALE_VALUE_16, PRESCALE_VALUE_64
}TWI_Prescalar;

/*enum that holds the index value of the slave addresses which are saved in the g_slaveAddresses*/
typedef enum{
	MY_ADDRESS , EEPROM_ADDRESS
}TWI_Address;

/*enum that holds the index value of the bit rates which are saved in the g_slaveAddresses*/
typedef enum{
	BIT_RATE_100kps , BIT_RATE_400kps, BIT_RATE_1mps, BIT_RATE_34mps
}TWI_BitRate;

typedef struct {
	TWI_Address address;
	TWI_BitRate bit_rate;
	TWI_Prescalar prescalar;
}TWI_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(void);
void TWI_init1(const TWI_ConfigType *  Config_Ptr );
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);


#endif /* TWI_H_ */
