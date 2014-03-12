/*
 * board.c
 *
 *  Created on: Nov 8, 2012
 *      Author: rasmus
 */


#include <avr/io.h>
#include "board.h"
#include "pwm.h"

#define LED_PIN PC4
#define LED_DDR DDRC
#define LED_PORT PORTC
#define LED_PWM_CHANNEL 0

void boardInit () {

	LED_DDR |= _BV(LED_PIN);	// Normal output
//	DDRC |= _BV(PORTC1);		//PWM output

}

void redLEDon() {

	PORTC |= _BV(LED_PIN);
}

void redLEDoff() {

	PORTC &= ~_BV(LED_PIN);
}

void redLEDtoggle() {

	PORTC ^= _BV(LED_PIN);
}
