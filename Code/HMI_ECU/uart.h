 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
typedef enum{
	UART_BitData_5 = 0, UART_BitData_6, UART_BitData_7, UART_BitData_8, UART_BitData_9 = 7
}UART_BitData;
typedef enum{
	UART_Parity_DISABLED = 0, UART_Parity_RESERVED, UART_Parity_EVEN, UART_Parity_ODD
}UART_Parity;

typedef enum{
	UART_StopBit_1 = 0, UART_StopBit_2
}UART_StopBit;

typedef enum{
	UART_BaudRate_RATE_10 = 10, UART_BaudRate_RATE_300 = 300, UART_BaudRate_RATE_600 = 600, UART_BaudRate_RATE_1200 = 1200,
	UART_BaudRate_RATE_2400 = 2400, UART_BaudRate_RATE_4800 = 4800, UART_BaudRate_RATE_9600 = 9600,
	UART_BaudRate_RATE_14400 = 14400, UART_BaudRate_RATE_19200 = 19200, UART_BaudRate_RATE_38400 = 38400,
	UART_BaudRate_RATE_57600 = 57600, UART_BaudRate_RATE_115200 = 115200,
	UART_BaudRate_RATE_128000 = 128000, UART_BaudRate_RATE_256000 = 256000
}UART_BaudRate;


typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 UART_BaudRate baud_rate;
}UART_ConfigType;
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

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
