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
#include <stdbool.h>
#include <stdlib.h>
#include "board.h"
#include "motor.h"

bool motorDirReversed = false;

void motorInit () {

	// TIMER1 init
	// Creates a PWM waveform
	TCCR1A |= _BV(COM1A1) | _BV(COM1B1);	// Non-inverted PWM waveform
	TCCR1B |= _BV(WGM13) | _BV(CS10);		// PFC PWM mode, start timer at Fcpu
	ICR1 = 0x7FFF;							// Set PWM resolution (15 bits)

	// Set all DC to zero
	_motorSetDutyCycleChannelA( 0x00 );
	_motorSetDutyCycleChannelB( 0x00 );

	// Enable the motor driver chip
	motorEnable();

}

void motorEnable() {
	boardMotorEnable();
}

void motorDisable() {
	boardMotorDisable();
}

void _motorSetDutyCycleChannelA(uint16_t newDutyCycle) {
	OCR1A = newDutyCycle;
}

void _motorSetDutyCycleChannelB(uint16_t newDutyCycle) {
	OCR1B = newDutyCycle;
}

void motorSetSpeed( int16_t newMotorSpeed ) {

	if (newMotorSpeed == 0) {

		// Shut down all PWM generation
		_motorSetDutyCycleChannelA( 0x00 );
		_motorSetDutyCycleChannelB( 0x00 );

	} else {

		if (motorDirReversed) {
			newMotorSpeed = -newMotorSpeed;
		}

		if (newMotorSpeed > 0) {

			_motorSetDutyCycleChannelB( 0x00 );
			_motorSetDutyCycleChannelA( abs(newMotorSpeed) );

		} else {

			_motorSetDutyCycleChannelA( 0x00 );
			_motorSetDutyCycleChannelB( abs(newMotorSpeed) );
		}

	}
}
