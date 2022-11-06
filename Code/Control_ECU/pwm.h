/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for the PWM driver
 *
 * Author: Omar Ahmed Anwar Mansour
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define MAX_VALUE_FOR_OCR0  256
#define PWM_OC0_PORT_ID     PORTB_ID
#define PWM_OC0_PIN_ID      PIN3_ID


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum{
	NoClockSource = 0, NoPrescaling, CLK_8, CLK_64, CLK_256, CLK_1024
}CLOCK_SELECT_PRESCALER;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * 		The function responsible for trigger the Timer0 with the PWM Mode.
 * 		Setup the PWM mode with Non-Inverting.
 * 		Setup the prescaler with F_CPU/8.
 * 		Setup the compare value based on the required input duty cycle
 * 		Setup the direction for OC0 as output pin through the GPIO driver.
 * 		The generated PWM signal frequency will be 500Hz to control the DC
 *		Motor speed.
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
