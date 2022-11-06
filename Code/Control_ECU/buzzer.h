 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer driver
 *
 * Author: Omar Ahmed Anwar Mansour
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Buzzer HW Ports and Pins Ids */
#define BUZZER_PORT_ID		PORTC_ID
#define BUZZER_PIN_ID		PIN3_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * 		Initialization function of the buzzer
 */
void Buzzer_init(void);

/*
 * Description :
 * 		Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void);

/*
 * Description :
 * 		Function to disable the Buzzer through the GPIO.
 */
void Buzzer_off(void);


#endif /* BUZZER_H_ */
