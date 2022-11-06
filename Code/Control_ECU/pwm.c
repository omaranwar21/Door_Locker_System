/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM driver
 *
 * Author: Omar Ahmed Anwar Mansour
 *
 *******************************************************************************/



#include "pwm.h"
#include <avr/io.h>
#include "gpio.h"


void PWM_Timer0_Start(uint8 duty_cycle){

	/* trigger the Timer0 with the FAST PWM Mode
	 * 		WGMOO = 1
	 * 		WGN01 = 1
	 *
	 * Setup the PWM mode with Non-Inverting
	 * 		COM00 = 0
	 * 		COM01 = 1
	 *
	 * Setup the prescaler with F_CPU/8
	 * 		CS00 = 0
	 * 		CS01 = 1
	 * 		CS02 = 0
	 *
	 * 	Setup the compare value based on the required input duty cycle
	 * 		TCNT0 = 0    (INTIALIZING THE COUNTER FROM ZERO)
	 * 		OCR0 = duty cycle VALUE   (COMPARING VALUE)
	 *
	 *	Setup the direction for OCR0 as output pin through the GPIO driver
	 *
	 *
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01);

	TCCR0 = (TCCR0 & 0XF8) | CLK_8;

	TCNT0 = 0;

	switch (duty_cycle) {
	case 100:
		/*  TO PREVENT 256 VALUE (it leads to stop the MOTOR because of the overflow)*/
		OCR0 = (((uint16)(duty_cycle*MAX_VALUE_FOR_OCR0))/100)-1;
		break;
	default:
		OCR0 = (((uint16)(duty_cycle*MAX_VALUE_FOR_OCR0))/100);
		break;
	}

	/* Clear OC2 on compare match, set OC2 at BOTTOM,
	 * (non-inverting mode)
	 */
	GPIO_setupPinDirection(PWM_OC0_PORT_ID, PWM_OC0_PIN_ID, PIN_OUTPUT);

}
