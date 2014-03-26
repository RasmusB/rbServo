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

#include <avr/eeprom.h>

#include "eepromConfig.h"

// Node specific configuration data is saved in EEPROM.
// These are the default values that must be changed after flashing.
uint8_t	EEMEM	eeprom_BootStayIn = 0;
uint8_t	EEMEM	eeprom_canbusNodeID = 0;

uint8_t	EEMEM	eeprom_vBattScaleValueA = 121;
uint8_t	EEMEM	eeprom_vBattScaleValueB = 16;

uint8_t	EEMEM	eeprom_sensorPotScaleValueA = 225;
uint8_t	EEMEM	eeprom_sensorPotScaleValueB = 128;
int16_t	EEMEM	eeprom_sensorPotScaleOffset = -900;

// Global variables, accessible after eepromReadConfiguration()
uint8_t			BootStayIn;
uint8_t			canbusNodeID;

uint8_t			sensorVBattScaleValueA;
uint8_t			sensorVBattScaleValueB;

uint8_t			sensorPotScaleValueA;
uint8_t			sensorPotScaleValueB;
int16_t			sensorPotScaleOffset;

void eepromReadConfiguration () {

	BootStayIn		= eeprom_read_byte(&eeprom_BootStayIn);
	canbusNodeID	= eeprom_read_byte(&eeprom_canbusNodeID);

	sensorVBattScaleValueA = eeprom_read_byte(&eeprom_vBattScaleValueA);
	sensorVBattScaleValueB = eeprom_read_byte(&eeprom_vBattScaleValueB);

	sensorPotScaleValueA = eeprom_read_byte(&eeprom_sensorPotScaleValueA);
	sensorPotScaleValueB = eeprom_read_byte(&eeprom_sensorPotScaleValueB);
	sensorPotScaleOffset = eeprom_read_word(&eeprom_sensorPotScaleOffset);

}

void eepromWriteConfiguration () {

	eeprom_update_byte(&eeprom_BootStayIn, BootStayIn);
	eeprom_update_byte(&eeprom_canbusNodeID, canbusNodeID);

}
