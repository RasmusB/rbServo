/*
 * main.c
 *
 *  Created on: Oct 25, 2012
 *      Author: rasmus
 */

// TODO: Create timer with mS resolution for PID loop

#include <avr/io.h>

#include "pwm.h"
#include "board.h"
#include "canbus.h"
#include "sensors.h"
#include "eepromConfig.h"

void init(void) __attribute__((constructor));

int main () {

	uint8_t i;
	uint8_t j;
	uint16_t rxID;
	uint8_t rxDLC;
	// TODO: Check for new CAN data. Update behavior accordingly.

	// TODO: Check if enough time has elapsed. If so, update PID.
	// TODO: Update PWM output according to PID output

	// TODO: Update remote CAN frame data
		/*	disable "data valid" flag
		 *	write new data to buffer
		 *	set "data valid" flag
		 */

	redLEDpwm(0);
	while (1) {

		canbusRXsetup(0);

		// Busy-Wait for a CAN message
		while (CANSTMOB == 0);
		CANSTMOB = 0x00;

		rxID = (CANIDT1 << 3) + (CANIDT2 >> 5);
		rxDLC = CANCDMOB & 0x0F;

		//redLEDpwm(CANIDT1);

		for (i=0; i < rxDLC; i++) {
			canbusDataBuffer[i] = CANMSG;
		}

		// Send message
		canbusTXsetup(rxID, rxDLC, 0);
	}



	return 0;
}

void init() {
	boardInit();
	//eepromReadConfiguration();
	//adcInit();

	pwmInit();

	canbusInit();

	// TODO: Initialize PID with EEPROM values
		// TODO: PID setpoint = current position
	//redLEDoff();

	// First boot since reflash via bootloader
	/*
	if (BootStayIn) {
		BootStayIn = 0;
		eepromWriteConfiguration();
	}
	*/
	// Enable Global Interrupts
	SREG |= _BV(SREG_I);

	// TODO: Send CANBUS "Application Ready"
	// TODO: Wait for CANBUS "OK" response

}
