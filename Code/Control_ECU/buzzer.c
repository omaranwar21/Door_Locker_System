 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer driver
 *
 * Author: Omar Ahmed Anwar Mansour
 *
 *******************************************************************************/

#include "gpio.h"
#include "common_macros.h"
#include "buzzer.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * 		Function to enable the Buzzer through the GPIO.
 */
void Buzzer_init(void){

	/*
	 * Setup the direction for the buzzer pin as output pin through the
	 * GPIO driver.
	 */
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);

	/*
	 *  Turn off the buzzer through the GPIO.
	 */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);

}

/*
 * Description :
 * 		Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void){

	/*
	 * Enable the Buzzer through the GPIO.
	 */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/*
 * Description :
 * 		Function to disable the Buzzer through the GPIO.
 */
void Buzzer_off(void){

	/*
	 * Disable the Buzzer through the GPIO.
	 */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
