/*
 * HMI_ECU.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Anwar
 */

#include "HMI_ECU.h"

UART_ConfigType HMI_UART = {
	UART_BitData_8,
	UART_Parity_DISABLED,
	UART_StopBit_1,
	UART_BaudRate_RATE_9600
};

Timer1_ConfigType HMI_Timer1 = {
		0,
		7813,
		TIMER1_PRESCALER_1024,
		TIMER1_COMPARE_MODE
};

uint8 g_Tick = 0;

void HMI_creatPass(void){
	uint8 firstPass[PASS_SIZE+1];
	uint8 secondPass[PASS_SIZE+1];
	uint8 correct;

	UART_init(&HMI_UART);

	HMI_enterPassDisplay();

	HMI_getPass(firstPass);

	LCD_clearScreen();
	LCD_displayString("Plz re-enter the ");
	LCD_moveCursor(1, 0);
	LCD_displayString("same pass: ");

	HMI_getPass(secondPass);

	HMI_Ready();

	UART_sendByte(HMI_FIRST_PASS);
	while(UART_recieveByte() != MICRO_READY);
	UART_sendString(firstPass);

	while(UART_recieveByte() != MICRO_READY);

	HMI_Ready();
	UART_sendByte(HMI_SECOND_PASS);
	while(UART_recieveByte() != MICRO_READY);
	UART_sendString(secondPass);


	while(UART_recieveByte() != MICRO_READY);
	correct = UART_recieveByte();

	if (!correct) {
		LCD_clearScreen();
		HMI_creatPass();
	}
	else {
		LCD_clearScreen();
		HMI_options();
	}
}

void HMI_options(void){
	uint8 key = 0;
	LCD_clearScreen();
	LCD_displayString("+ : Open Door");
	LCD_moveCursor(1, 0);
	LCD_displayString("- : Change Pass");
	key = KEYPAD_getPressedKey();
	_delay_ms(KEYPAD_DELAY);

	switch (key) {
		case '+':
			HMI_openDoor();
			break;
		case '-':
			HMI_changePass();
			break;
		default:
			HMI_passCheching();
	}
}


void HMI_openDoor(void){
	uint8 correct;
	HMI_enterPassDisplay();
	correct = HMI_passCheching();

	if (correct) {
		HMI_openAction();
	}
	else {
		HMI_ErrorAction();
	}

}


void HMI_changePass(void){
	uint8 check;
	check = HMI_passCheching();

	if (check) {
		HMI_creatPass();
	}
	else {
		HMI_ErrorAction();
	}

}

uint8 HMI_passCheching(void){
	uint8 pass[PASS_SIZE+1];
	uint8 checkPass;
	uint8 loop;
	for (loop = 0; loop < HMI_TRIALS; ++loop) {
		LCD_clearScreen();
		HMI_enterPassDisplay();
		HMI_getPass(pass);

		HMI_Ready();
		UART_sendByte(HMI_CHECK_PASS);
		while(UART_recieveByte() != MICRO_READY);
		UART_sendString(pass);

		while(UART_recieveByte() != MICRO_READY);
		checkPass = UART_recieveByte();

		if (checkPass) {
			return 1;
		}
		else {
			continue;
		}

	}
	return 0;
}

void HMI_enterPassDisplay(void){
	LCD_clearScreen();
	LCD_displayString("Plz Enter Pass: ");
	LCD_moveCursor(1, 0);
}


void HMI_getPass(uint8*pass){

	uint8 loop;
	for (loop = 0; loop < PASS_SIZE; ++loop) {
		pass[loop] = KEYPAD_getPressedKey();
		_delay_ms(KEYPAD_DELAY);
		LCD_displayCharacter('*');
	}

	while(KEYPAD_getPressedKey() != ENTER_BUTTON);
	_delay_ms(KEYPAD_DELAY);
	pass[PASS_SIZE] = '#';

}


void HMI_Ready(void){
	UART_sendByte(MICRO_READY);
	while(UART_recieveByte() != MICRO_READY);
}

void HMI_ErrorAction(void){
	HMI_Ready();
	UART_sendByte(HMI_ERROR_ACTION);

	LCD_clearScreen();
	Timer1_setCallBack(HMI_Stuck);
	Timer1_init(&HMI_Timer1);
	LCD_displayString("ERROR");


	while (g_Tick < 60);

	Timer1_deInit();
	g_Tick = 0;
	HMI_options();
}

void HMI_openAction(void){
	HMI_Ready();
	UART_sendByte(HMI_OPEN_ACTION);

	while(UART_recieveByte() != MICRO_READY);

	LCD_clearScreen();

	LCD_displayString("Door is ");
	LCD_displayStringRowColumn(1, 0, "Unlocking");

	Timer1_setCallBack(HMI_Stuck);
	Timer1_init(&HMI_Timer1);


	while(g_Tick < 15);

	LCD_clearScreen();
	LCD_displayString("...");

	while(g_Tick < 19);

	LCD_clearScreen();
	LCD_displayString("Door is Locking");

	while(g_Tick < 34);

	g_Tick = 0;
	Timer1_deInit();
	HMI_options();
}

void HMI_Stuck(void){
	g_Tick++;
}




