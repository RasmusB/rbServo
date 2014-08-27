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

#include "adc.h"
#include "board.h"
#include "eepromConfig.h"

void sensorInit() {
	// TODO: Lägg till nåt...
}

uint16_t sensorVBattGetRaw() {
	return adGetValueVbatt();
}

uint16_t sensorVBattGetValue() {
	uint32_t temp = adGetValueVbatt();
	temp = (uint32_t) (temp * sensorVBattScaleValueA);
	temp = (uint16_t) (temp / sensorVBattScaleValueB);

	return temp;
}

uint16_t sensorPotGetRaw() {
	return adGetValuePot();
}

int16_t sensorPotGetValue() {
	int32_t temp = adGetValuePot();
	// TODO : Make the "magic numbers" calibration parameters
	temp = (int32_t) (temp * sensorPotScaleValueA);
	temp = (int32_t) (temp / sensorPotScaleValueB);
	temp = temp + sensorPotScaleOffset;

	return (int16_t) temp;
}

uint16_t sensorIsenseGetRaw() {
	return adGetValueIsense();
}

uint16_t sensorIsenseGetValue() {
	uint32_t temp = adGetValueIsense();
	temp = (uint32_t) (temp * sensorIsenseScaleValueA);
	temp = (uint16_t) (temp / sensorIsenseScaleValueB);

	return temp;
}

