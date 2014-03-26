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
#include <stdlib.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "board.h"
#include "canbus.h"
#include "eepromConfig.h"
//#include "pid.h"
#include "pwm.h"
#include "sensors.h"
#include "timer.h"

void init(void) __attribute__((constructor));

extern uint16_t sensorPotGetRaw();

uint8_t mirrorMCUSR __attribute__ ((section (".noinit")));

int main () {

	uint8_t i;
	uint16_t rxID;
	uint8_t rxDLC;

	char asciiMessage[9];

	uint8_t msgChoice;

	mirrorMCUSR = MCUSR;

	//pwmSetDutyCycle( 0xFFFF );

	// TODO: Check for new CAN data. Update behavior accordingly.

	// TODO: Check if enough time has elapsed. If so, update PID.
	// TODO: Update PWM output according to PID output

	// TODO: Update remote CAN frame data
		/*	disable "data valid" flag
		 *	write new data to buffer
		 *	set "data valid" flag
		 */

	while (1) {

		uint16_t tempVBatt = sensorVBattGetValue();
		uint16_t tempVBattRaw = sensorVBattGetRaw();
		int16_t tempPot = sensorPotGetValue();
		uint16_t tempPotRaw = sensorPotGetRaw();

		pwmSetRedLEDdutyCycle( tempPotRaw >> 6 );

		if (secondTick > 0) {
			secondTick = 0;

			if (msgChoice & 1) {

				itoa(tempVBatt, asciiMessage, 10);

				for (i=0; i < 4; i++) {
					canbusTxBuffer[i] = asciiMessage[i];
				}

				canbusTxBuffer[6] = (uint8_t) tempVBattRaw >> 6;
				canbusTxBuffer[7] = (uint8_t) tempVBattRaw;

				canbusTXsetup(000, 8, 0);

			} else {

				itoa(tempPot, asciiMessage, 10);

				for (i=0; i < 4; i++) {
					canbusTxBuffer[i] = asciiMessage[i];
				}

				canbusTxBuffer[6] = (uint8_t) tempPotRaw >> 6;
				canbusTxBuffer[7] = (uint8_t) tempPotRaw;

				canbusTXsetup(010, 8, 0);

			}

			msgChoice++;

		}



//		canbusRXsetup(0);
//
//		// Busy-Wait for a CAN message
//		while (CANSTMOB == 0);
//		CANSTMOB = 0x00;
//
//		rxID = (CANIDT1 << 3) + (CANIDT2 >> 5);
//		rxDLC = CANCDMOB & 0x0F;
//
//		for (i=0; i < rxDLC; i++) {
//			canbusRxDataBuffer[i] = CANMSG;
//		}
//
//		if (rxID == 0x123 && rxDLC == 2) {
//			pwmSetDutyCycle((canbusRxDataBuffer[0] << 8) + canbusRxDataBuffer[1]);
//		}
//
//		//canbusTXsetup(rxID, rxDLC, 0); 	// This just echos the last received message

	}



	return 0;
}

void init() {
	// Read all node configuration data
	eepromReadConfiguration();

	// Initialize board IO
	boardInit();

	// Initialize AD converter
	adcInit();

	// Initialize PWM generation
	pwmInit();

	// Initialize timer-based interrupts
	timerInit();

	canbusInit();

	// TODO: Initialize PID with EEPROM values
	// TODO: PID setpoint = current position

	// Enable Global Interrupts
	sei();
}
