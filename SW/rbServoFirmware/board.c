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
#include "pwm.h"

#define RED_LED_PIN PC4
#define RED_LED_DDR DDRC
#define RED_LED_PORT PORTC

#define MOTOR_EN_PIN PB4
#define MOTOR_EN_DDR DDRB
#define MOTOR_EN_PORT PORTB

#define MOTOR_FAULT_PIN PD0
#define MOTOR_FAULT_DDR DDRD
#define MOTOR_FAULT_PORT PORTD

void boardInit () {

	RED_LED_DDR |= _BV(RED_LED_PIN);	// Normal output
	MOTOR_EN_DDR |= _BV(MOTOR_EN_PIN);	// Normal output
	// MOTOR_FAULT_DDR already input
}

void motorENon() {

	MOTOR_EN_PORT |= _BV(MOTOR_EN_PIN);
}

void motorENoff() {

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
