/*
 * test_HMI.c
 *
 *  Created on: Nov 3, 2022
 *      Author: Anwar
 */
#include "HMI_ECU.h"

int main(int argc, char **argv) {
	SREG |= (1<<7);
	LCD_init();
	_delay_ms(100);
	HMI_creatPass();
}
