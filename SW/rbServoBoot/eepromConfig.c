/*
 * eepromConfig.c
 *
 *  Created on: Oct 30, 2012
 *      Author: rasmus
 */

#include <avr/eeprom.h>

#include "eepromConfig.h"

// Node specific configuration data is saved in EEPROM.
// These are the default values that must be changed after flashing.
uint8_t		EEMEM	eeprom_BootStayIn = 0;
uint8_t		EEMEM	eeprom_canbusNodeID = 0;
uint8_t		EEMEM	eeprom_pidEnabled = 0;
uint8_t		EEMEM	eeprom_pidReversed = 0;

uint16_t	EEMEM	eeprom_pidSampleTime = 0;

float		EEMEM	eeprom_pidKp = 0.0;
float		EEMEM	eeprom_pidKi = 0.0;
float		EEMEM	eeprom_pidKd = 0.0;
float		EEMEM	eeprom_pidOutputMin = 0.0;
float		EEMEM	eeprom_pidOutputMax = 0.0;


// Global variables, accessible after eepromReadConfiguration()
uint8_t		BootStayIn;
uint8_t		canbusNodeID;
uint8_t		pidEnabled;
uint8_t		pidReversed;

uint16_t	pidSampleTime;

float		pidKp;
float		pidKi;
float		pidKd;
float		pidOutputMin;
float		pidOutputMax;


void eepromReadConfiguration () {

	BootStayIn		= eeprom_read_byte(&eeprom_BootStayIn);
	canbusNodeID	= eeprom_read_byte(&eeprom_canbusNodeID);
	pidEnabled		= eeprom_read_byte(&eeprom_pidEnabled);
	pidReversed		= eeprom_read_byte(&eeprom_pidReversed);

	pidSampleTime	= eeprom_read_word(&eeprom_pidSampleTime);

	pidKp			= eeprom_read_float(&eeprom_pidKp);
	pidKi			= eeprom_read_float(&eeprom_pidKi);
	pidKd			= eeprom_read_float(&eeprom_pidKd);
	pidOutputMin	= eeprom_read_float(&eeprom_pidOutputMin);
	pidOutputMax	= eeprom_read_float(&eeprom_pidOutputMax);

}

void eepromWriteConfiguration () {

	eeprom_update_byte(&eeprom_BootStayIn, BootStayIn);
	eeprom_update_byte(&eeprom_canbusNodeID, canbusNodeID);
	eeprom_update_byte(&eeprom_pidEnabled, pidEnabled);
	eeprom_update_byte(&eeprom_pidReversed, pidReversed);

	eeprom_update_word(&eeprom_pidSampleTime, pidSampleTime);

	eeprom_update_float(&eeprom_pidKp, pidKp);
	eeprom_update_float(&eeprom_pidKi, pidKi);
	eeprom_update_float(&eeprom_pidKd, pidKd);
	eeprom_update_float(&eeprom_pidOutputMin, pidOutputMin);
	eeprom_update_float(&eeprom_pidOutputMax, pidOutputMax);

}
