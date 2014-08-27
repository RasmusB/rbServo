/*
The MIT License (MIT)

Copyright (c) 2014 Rasmus Backman

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include <avr/io.h>
#include "board.h"
#include "timer.h"

#define RED_LED_PIN PC5
#define RED_LED_DDR DDRC
#define RED_LED_PORT PORTC

#define GRN_LED_PIN PC6
#define GRN_LED_DDR DDRC
#define GRN_LED_PORT PORTC

#define MOTOR_EN_PIN PB2
#define MOTOR_EN_DDR DDRB
#define MOTOR_EN_PORT PORTB

#define MOTOR_FAULT_PIN PD0
#define MOTOR_FAULT_DDR DDRD
#define MOTOR_FAULT_PORT PORTD

#define MOTOR_PWMA_PIN PD2
#define MOTOR_PWMA_DDR DDRD
#define MOTOR_PWMA_PORT PORTD

#define MOTOR_PWMB_PIN PC1
#define MOTOR_PWMB_DDR DDRC
#define MOTOR_PWMB_PORT PORTC

void boardInit () {

	RED_LED_DDR |= _BV(RED_LED_PIN);		// Normal output
	GRN_LED_DDR |= _BV(GRN_LED_PIN);		// Normal output
	MOTOR_EN_DDR |= _BV(MOTOR_EN_PIN);		// Normal output
	// MOTOR_FAULT_DDR is input by default
	MOTOR_PWMA_DDR |= _BV(MOTOR_PWMA_PIN);	// Controlled by HW PWM
	MOTOR_PWMB_DDR |= _BV(MOTOR_PWMB_PIN);	// Controlled by HW PWM
}

void boardMotorEnable() {

	MOTOR_EN_PORT |= _BV(MOTOR_EN_PIN);
}

void boardMotorDisable() {

	MOTOR_EN_PORT &= ~_BV(MOTOR_EN_PIN);
}

void redLEDon() {

	RED_LED_PORT |= _BV(RED_LED_PIN);
}

void redLEDoff() {

	RED_LED_PORT &= ~_BV(RED_LED_PIN);
}

void redLEDtoggle() {

	RED_LED_PORT ^= _BV(RED_LED_PIN);
}

void redLEDpwm( uint8_t dutyCycle ) {

	timerSetRedLEDdutyCycle ( dutyCycle );
}

void grnLEDon() {

	GRN_LED_PORT |= _BV(GRN_LED_PIN);
}

void grnLEDoff() {

	GRN_LED_PORT &= ~_BV(GRN_LED_PIN);
}

void grnLEDtoggle() {

	GRN_LED_PORT ^= _BV(GRN_LED_PIN);
}

void grnLEDpwm( uint8_t dutyCycle ) {

	timerSetGrnLEDdutyCycle ( dutyCycle );
}
