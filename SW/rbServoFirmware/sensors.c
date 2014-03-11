/*
 * sensors.c
 *
 *  Created on: Nov 9, 2012
 *      Author: rasmus
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#include "board.h"

#define ADC_CHANNEL_VBATT 3
#define ADC_CHANNEL_POT 4

#define ADMUX_VBATT 0x43
#define ADMUX_POT 0x44

#define ADBUFFER_VBATT 0
#define ADBUFFER_POT 1

#define noOfSensors 2

static int16_t _XYmap(int16_t, int16_t, int16_t, int16_t, int16_t);
static uint8_t _readADC8bit(void);
static uint16_t _readADC16bit(void);

volatile uint16_t sensorRawValue[noOfSensors];

void sensorInit() {
	// TODO: Lägg till nåt...
}

void adcInit() {

	// Set prescaler to 8 (16Mhz/8 = 2MHz)
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

	ADMUX = ADMUX_POT;

	ADCSRA |= _BV(ADEN) | _BV(ADIE);	// Enable ADC & interrupt
	ADCSRA |= _BV(ADSC);					// Start first conversion
}

uint16_t sensorVBattGetRaw() {
	return sensorRawValue[ADBUFFER_VBATT];
}

uint16_t sensorVBattGetValue() {
	uint32_t temp = sensorRawValue[ADBUFFER_VBATT];
	// TODO : Make the "magic numbers" calibration parameters
	temp = (uint32_t) (temp * 121);
	temp = (uint16_t) (temp / 16);

	return temp;
}

uint16_t sensorPotGetRaw() {
	return sensorRawValue[ADBUFFER_POT];
}

int16_t sensorPotGetValue() {
	int32_t temp = sensorRawValue[ADBUFFER_POT];
	// TODO : Make the "magic numbers" calibration parameters
	temp = (int32_t) (temp * 225);
	temp = (int32_t) (temp / 128);
	temp = temp - 900;

	return (int16_t) temp;
}

ISR(ADC_vect) {

	if ( ADMUX  == ADMUX_VBATT ) {
		sensorRawValue[ADBUFFER_VBATT] = ADCL;
		sensorRawValue[ADBUFFER_VBATT] += (ADCH << 8);
		ADMUX = ADMUX_POT;
	}
	else if (ADMUX == ADMUX_POT ) {
		sensorRawValue[ADBUFFER_POT] = ADCL;
		sensorRawValue[ADBUFFER_POT] += (ADCH << 8);
		ADMUX = ADMUX_VBATT;
	}

	ADCSRA |= _BV(ADSC);	// Start next conversion

}

static int16_t _XYmap( int16_t x, int16_t xMin, int16_t xMax, int16_t yMin, int16_t yMax) {

	return (x - xMin) * (yMax - yMin) / (xMax - xMin) + yMin;
}

static uint8_t _readADC8bit(void) {
	// Returns the conversion result at a
	// specific width of 8 bits.
	// Assumes ADLAR=1 in ADMUX!

	return ADCH;
}

static uint16_t _readADC16bit(void) {
	// Returns the conversion result at a
	// specific width of 16 bits.
	// Assumes ADLAR=1 in ADMUX!

	int16_t temp;

	temp = ADCL;
	temp += (ADCH << 8);

	return temp;
}


