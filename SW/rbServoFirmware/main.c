/*
 * main.c
 *
 *  Created on: Oct 25, 2012
 *      Author: rasmus
 */

// TODO: Create timer with mS resolution for PID loop

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "pwm.h"
#include "board.h"
#include "canbus.h"
#include "sensors.h"
#include "eepromConfig.h"

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

//		pwmSetDutyCycle( tempPotRaw << 6 );

		if (messageTick > 0) {
			messageTick = 0;

			if (msgChoice & 1) {

				canbusTxBuffer[0] = (uint8_t) (tempPot >> 8);
				canbusTxBuffer[1] = (uint8_t) (tempPot);
				canbusTxBuffer[2] = (uint8_t) (tempPotRaw >> 8);
				canbusTxBuffer[3] = (uint8_t) (tempPotRaw);
				canbusTXsetup(000, 4, 0);

			} else {

				itoa(tempPot, asciiMessage, 10);

				for (i=0; i < 8; i++) {
					canbusTxBuffer[i] = asciiMessage[i];
				}
				canbusTXsetup(010, 8, 0);

			} msgChoice++;

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
	boardInit();
	//eepromReadConfiguration();
	adcInit();

	pwmInit();

	canbusInit();

	// TODO: Initialize PID with EEPROM values
	// TODO: PID setpoint = current position


	// Enable Global Interrupts
	sei();

	// TODO: Send CANBUS "Application Ready"
	// TODO: Wait for CANBUS "OK" response

}
