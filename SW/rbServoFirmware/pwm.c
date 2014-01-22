/*
 * pwm.c
 *
 *  Created on: Nov 9, 2012
 *      Author: rasmus
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "pwm.h"

#define PWMCHANNELS 3
// CHANNEL 00 = RED LED

#define PWMMASK_PORTB 0x00
#define PWMMASK_PORTC 0x10 // PWM on PC4
#define PWMMASK_PORTD 0x00

uint8_t pwmDutyCycle[PWMCHANNELS];

uint8_t pwmNextPinStatePortB;
uint8_t pwmNextPinStatePortC;
uint8_t pwmNextPinStatePortD;

void pwmInit () {

	// Set up Timer0 to run at full speed
	TCCR0B |= _BV(CS00);

	// Enable overflow interrupt
	TIMSK0 |= _BV(TOIE0);
}

void pwmSetDutyCycle (uint8_t pwmChannel, uint8_t newDutyCycle) {
	if (!pwmChannel < PWMCHANNELS) {
		pwmDutyCycle[pwmChannel] = newDutyCycle;
	} // Silently ignore errors
}

ISR(TIMER0_OVF_vect) {
	// Initialize start conditions
	static uint8_t pwmDutyCycleCounter = 0xFF;
	static uint8_t pwmDutyCycleBuffer[PWMCHANNELS];

	if ( pwmDutyCycleCounter == 0xFF ) {
		PORTC &= ~_BV(PC4);
		pwmDutyCycleBuffer[0] = pwmDutyCycle[0];
	}

	if ( pwmDutyCycleCounter == pwmDutyCycleBuffer[0] ) {
		PORTC |= _BV(PC4);
	}

	pwmDutyCycleCounter--;
}
