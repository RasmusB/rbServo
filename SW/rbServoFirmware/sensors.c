/*
 * sensors.c
 *
 *  Created on: Nov 9, 2012
 *      Author: rasmus
 */
#include <avr/io.h>

#define ADC3 3

// Static function prototoyes
static int16_t _XYmap(int16_t, int16_t, int16_t, int16_t, int16_t);
static int16_t _readADC(void);


void adcInit() {
	// Set prescaler to 8 (16Mhz/8 = 2MHz)
	ADCSRA |= _BV(ADPS1) | _BV(ADPS0);

	// Select reference voltage
	// TODO: Rev B: Add support for different references
	ADMUX |= _BV(REFS1) | _BV(REFS0); // DONT CHANGE FOR REV A!!


}

static int16_t _XYmap( int16_t x, int16_t xMin, int16_t xMax, int16_t yMin, int16_t yMax) {

	return (x - xMin) * (yMax - yMin) / (xMax - xMin) + yMin;
}

static int16_t _readADC(void) {
	return 0;
}
