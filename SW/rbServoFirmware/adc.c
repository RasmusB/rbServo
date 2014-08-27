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

#define AD_CHANNEL_COUNT 3

#define ADMUX_VBATT 0x42
#define ADBUFFER_VBATT 0

#define ADMUX_POT 0x46
#define ADBUFFER_POT 1

#define ADMUX_ISENSE 0xC8
#define ADBUFFER_ISENSE 2

volatile uint16_t adDataBuffer[AD_CHANNEL_COUNT];

uint16_t adGetValueVbatt( void ) {

	return adDataBuffer[ADBUFFER_VBATT];
}

uint16_t adGetValuePot( void ) {

	return adDataBuffer[ADBUFFER_POT];
}

uint16_t adGetValueIsense( void ) {

	return adDataBuffer[ADBUFFER_ISENSE];
}


void adcInit() {

	// Set prescaler to 8 (16Mhz/8 = 2MHz)
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

	// Enable internal Aref circuitry
	ADCSRB |= _BV(AREFEN);

	ADMUX = ADMUX_VBATT;

	ADCSRA |= _BV(ADEN) | _BV(ADIE);	// Enable ADC & interrupt
	ADCSRA |= _BV(ADSC);				// Start first conversion
}

ISR(ADC_vect) {

	// This interrupt is triggered when the conversion is done.
	// The result is saved to the correct buffer, and the ADMUX
	// register is updated before restarting the conversion.

	if ( ADMUX  == ADMUX_VBATT ) {
		adDataBuffer[ADBUFFER_VBATT] = ADCL;
		adDataBuffer[ADBUFFER_VBATT] += (ADCH << 8);
		ADMUX = ADMUX_POT;
	}
	else if (ADMUX == ADMUX_POT ) {
		adDataBuffer[ADBUFFER_POT] = ADCL;
		adDataBuffer[ADBUFFER_POT] += (ADCH << 8);
		ADMUX = ADMUX_ISENSE;
	}
	else if (ADMUX == ADMUX_ISENSE ) {
		adDataBuffer[ADBUFFER_ISENSE] = ADCL;
		adDataBuffer[ADBUFFER_ISENSE] += (ADCH << 8);
		ADMUX = ADMUX_VBATT;
	}

	ADCSRA |= _BV(ADSC);	// Start next conversion

}
