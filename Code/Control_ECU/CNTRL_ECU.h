/*
 * controlECU.h
 *
 *  Created on: Nov 5, 2022
 *      Author: Anwar
 */

#ifndef CNTRL_ECU_H_
#define CNTRL_ECU_H_

#include "buzzer.h"
#include "common_macros.h"
#include "dc_motor.h"
#include "external_eeprom.h"
#include "std_types.h"
#include "timer1.h"
#include "twi.h"
#include "uart.h"
#include <util/delay.h>
#include <avr/interrupt.h>

typedef enum{
	CNTRL_FIRST_PASS = 1, CNTRL_SECOND_PASS, CNTRL_CHECK_PASS,
	CNTRL_ERROR_ACTION, CNTRL_OPEN_ACTION
}CNTRL_mesages;

#define PASS_SIZE		5
#define MICRO_READY		0x10

void CNTRL_createPass(void);

uint8 CNTRL_isCorrect(uint8*, uint8*);

void CNTRL_savePass(uint8* pass);

uint8 CNTRL_compareSavedPass(uint8* pass);

void CNTRL_Ready(void);

void CNTRL_ErrorAction(void);

void CNTRL_OpenAction(void);

void CNTRL_Stuck(void);




#endif /* CNTRL_ECU_H_ */
