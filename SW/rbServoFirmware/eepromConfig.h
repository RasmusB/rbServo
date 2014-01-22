/*
 * eepromConfig.h
 *
 *  Created on: Oct 30, 2012
 *      Author: rasmus
 */

#ifndef EEPROMCONFIG_H_
#define EEPROMCONFIG_H_

// Global variables, accessible after eepromReadConfiguration()
extern uint8_t		BootStayIn;
extern uint8_t		canbusNodeID;
extern uint8_t		pidEnabled;
extern uint8_t		pidReversed;

extern uint16_t	pidSampleTime;

extern float		pidKp;
extern float		pidKi;
extern float		pidKd;
extern float		pidOutputMin;
extern float		pidOutputMax;

void eepromReadConfiguration ();
void eepromWriteConfiguration ();

#endif /* EEPROMCONFIG_H_ */
