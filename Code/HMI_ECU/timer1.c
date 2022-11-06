/*
 * timer1.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Anwar
 */
#include <avr/io.h>
#include "timer1.h"
#include "common_macros.h"
#include <avr/interrupt.h>
#include "lcd.h"

static volatile void (*g_callBackPtr)() = NULL_PTR;

ISR(TIMER1_OVF_vect)
{

	if(g_callBackPtr != NULL_PTR)
		{
			/* Setting the callback function */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			/* Setting the callback function */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}

void Timer1_init(const Timer1_ConfigType * Config_Ptr){

	TCNT1 = Config_Ptr->initial_value;		/* Set timer1 initial count to compare value in config structure */

	OCR1A = Config_Ptr->compare_value;    /* Set the Compare value to 125 ((125/500) * 100 = 25%) */

	/* Configure timer control register TCCR1A
	 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
	 * 2. FOC1A=1 FOC1B=0
	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
	 */
	TCCR1A |= (1<<FOC1A);

	/* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 2. Prescaler = F_CPU/8 CS10=0 CS11=1 CS12=0
	 */
	TCCR1B = (TCCR1B & 0xF8) | Config_Ptr->prescaler;
	TCCR1B = (TCCR1B & 0xF7) | (Config_Ptr->mode << 1);

	TIMSK = (1<<OCIE1A); /*Enable Timer1 Compare A Interrupt */
}

void Timer1_deInit(void){
	/*
	 * Disable Timer1 intrrupt
	 */
	TIMSK &= ~(1<<OCIE1A);
}

void Timer1_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr = a_ptr;
}



