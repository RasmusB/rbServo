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
#include <avr/interrupt.h>

#include "board.h"
#include "pwm.h"

volatile uint8_t secondTick;
volatile uint8_t redLEDdutyCycle;

void timerInit() {
	// TIMER0 init
	// Creates a 1ms interrupt
	TCCR0A |= _BV(WGM01);				//Enable CTC mode
	TIMSK0 |= _BV(OCIE0A);				// Enable compare interrupt
	OCR0A = 0xF9;						// Set timer TOP value to d249
	TCCR0B |= _BV(CS01) | _BV(CS00);	// Start Timer0 at Fcpu/64
}

void timerSetPWMdutyCycle ( uint8_t newDutyCycle ) {
	redLEDdutyCycle = newDutyCycle;
}

ISR(TIMER0_COMPA_vect) {
	static uint8_t pwmCycle;
	static uint16_t msec;

	// Update PWM cycle counter
	if (pwmCycle == 15) {
		pwmCycle = 0;
	} else pwmCycle++;

	// Update IO accordingly
	if (pwmCycle == 0 || pwmCycle >= redLEDdutyCycle) {
		redLEDoff();
	} else redLEDon();

	//Update Timer
	if (msec == 999) {
		msec = 0;
		secondTick++;
	} else {
		msec++;
	}

}
