/*
 * pwm.c
 *
 *  Created on: Nov 9, 2012
 *      Author: rasmus
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "pwm.h"

volatile uint8_t messageTick = 0;

void pwmInit () {

	// TIMER0 init
	// Creates a 1ms interrupt
	TCCR0A |= _BV(WGM01);				//Enable CTC mode
	TIMSK0 |= _BV(OCIE0A);				// Enable compare interrupt
	OCR0A = 0xF9;						// Set timer TOP value to d249
	TCCR0B |= _BV(CS01) | _BV(CS00);	// Start Timer0 at Fcpu/64

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

ISR(TIMER0_COMPA_vect) {
	static uint16_t msec;

	if (msec == 999) {
		msec = 0;
		messageTick++;
	} else {
		msec++;
	}

}

