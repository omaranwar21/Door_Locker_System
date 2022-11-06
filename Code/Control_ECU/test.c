/*
 * test.c
 *
 *  Created on: Nov 2, 2022
 *      Author: Anwar
 */
#include "twi.h"
#include "external_eeprom.h"
#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include <util/delay.h>
#include "CNTRL_ECU.h"

//TWI_ConfigType twi_Config_Ptr = {
//		ADDRESS_SLAVE, TWI_TWBR_VALUE
//};


int main(int argc, char **argv) {
	SREG |= (1<<7);
	Buzzer_init();
	DcMotor_Init();
	CNTRL_createPass();
}


