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
#include "pwm.h"
#include "timer.h"

void pwmInit () {
	// TIMER1 init
	// Creates a PWM waveform
	// TODO: Add a second channel for RevB
	TCCR1A |= _BV(COM1B1);				// Non-inverted PWM waveform
	TCCR1B |= _BV(WGM13) | _BV(CS10);	// PFC PWM mode, start timer at Fcpu
	ICR1 = 0xFFFF;						// Set PWM resolution
}

void pwmSetDutyCycle(uint16_t newDutyCycle) {
	OCR1B = newDutyCycle;
}

void pwmSetRedLEDdutyCycle(uint8_t newDutyCycle) {
	// SW PWM is handled by timer.c
	timerSetPWMdutyCycle ( newDutyCycle );
}

