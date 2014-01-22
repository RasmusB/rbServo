/*
 * canbus.c
 *
 *  Created on: Oct 30, 2012
 *      Author: rasmus
 */

#include <avr/io.h>
#include "canbus.h"

#define MAX_MOb 5

uint8_t canbusID;
uint8_t canbusDataBuffer[8];

//Static function prototyes
static uint8_t _canbusGetMOb( uint8_t prio );

void canbusInit () {
	uint8_t i;

	// Reset the CAN hardware. This kills all communication
	// and stays in stand-by mode until we are done configuring.
	CANGCON = _BV(SWRES);

	// TODO: Initialize any CAN code global variables here while the CAN hardware is idle

	// Clear status registers for all MOb:s
	for (i = 0; i <= 5; i++) {
		CANPAGE = i << MOBNB0;
		CANCDMOB = 0x00;
		CANSTMOB = 0x00;
	}

	// Write CANBT1, CANBT2 and CANBT3 with the CAN baud setup values
	// Current settings for 16 MHz system clock:
	// Rate = 125Kbit, SP = 75%, TQ = 1.250
	CANBT1 = 0x1E;
	CANBT2 = 0x04;
	CANBT3 = 0x13;

	// Write CANGIE to your desired configuration
	// TODO: Enable interrupts for emergency messages! Don't forget MOb-specific interrupts.
	CANGIE = (uint8_t) ~_BV(ENIT);
	CANIE1 = 0x00;
	CANIE2 = 0x00;

	// If desired write the CANHPMOB CGP3, CGP2, CGP1 and CGP0 bits
	// Typically the General register CANHPMOB reset default is the most useful

	// If you are using time stamping write CANTCON with any desired non-zero value

	// Setup complete, enable CAN controller
	CANGCON = _BV(ENASTB);
}



uint8_t canbusTXsetup( uint16_t messageID, uint8_t messageDLC, uint8_t prio ) {

	uint8_t i;
	uint8_t selectedMOb;

	// Mask CAN ID if 11-bit
	messageID = messageID & 0x07FF;

	// Check for available MOb, return if none
	selectedMOb = _canbusGetMOb(prio);
	if (selectedMOb == 0xFF) return 1;

	//	Select MOb. Also auto increment and byte buffer index 0.
	CANPAGE = (selectedMOb << 4) & 0xF0;

	//	Make sure the MOb CANSTMOB value is cleared
	//	The polling or interrupt code must finish with and clear CANSTMOB for this MOb first
	CANSTMOB = 0x00; 	//TODO: Is manual clearing of CANSTMOB OK in TX?

	//	Write CANIDT1, CANIDT2, CANIDT3 and CANIDT4 to the CAN ID value (see IDE bit below)
	//	Write CANIDT4.RTRTAG=0 for CAN Data Frame, or =1 for CAN Remote Frame
	//	Write all unused/reserved bits=0
	// TODO: Just dummy values for now... CANID = 0x001, data frame.

	CANIDT4 = 0x00;
	CANIDT3 = 0x00;
	CANIDT2 = (uint8_t) (messageID << 5);
	CANIDT1 = (uint8_t) (messageID >> 3);

	//	Write CANIDM1, CANIDM2, CANIDM3 and CANIDM4 all =0
	//	Not used for TX, only cleared for compatibility.

	CANIDM4 = 0x00;
	CANIDM3 = 0x00;
	CANIDM2 = 0x00;
	CANIDM1 = 0x00;

	//	Sequentially write all CANMSG bytes to be sent in the Tx (8 bytes maximum)
	//	If CANPAGE.AINC=0 the CANPAGE.INDXn value will auto-increment after each write
	//	If CANPAGE.AINC=1 you must change the CANPAGE.INDXn value for each CANMSG write

	for (i = 0; i < messageDLC; i++) {
		CANMSG = canbusDataBuffer[i];
	}

	//	1: Write CANCDMOB.CONMOBn=01 enable transmission
	//	2: Also write CANCDMOB.IDE=0 for 11 bit IDs, or =1 for 29 bit IDs
	//	3: Also write CANCDMOB.DLCn to match the number of CANMSG bytes written (8 bytes maximum)
	//	4: Also always write CANCDMOB.RPLV=0
	//	All four of these CANCDMOB register bit writes are all done together one time only for each MOb task
	// TODO: Change contents to actual values for DCL etc.
	CANCDMOB = _BV(CONMOB0) | messageDLC;

	while ( CANSTMOB != 0x40 );
	CANSTMOB = 0x00;

	return 0;	// Everything went well
}

uint8_t canbusRXsetup(uint8_t prio) {

	uint8_t i;
	uint8_t selectedMOb;

	// Check for available MOb, return if none
	selectedMOb = _canbusGetMOb(prio);
	if (selectedMOb == 0xFF) return 1;

	//	Select MOb. Also auto increment and byte buffer index 0.
	CANPAGE = (selectedMOb << 4);

	//	Make sure the MOb CANSTMOB value is cleared
	//	The polling or interrupt code must finish with and clear CANSTMOB for this MOb first
	CANSTMOB = 0x00; 	//TODO: Is manual clearing of CANSTMOB OK in RX?

	//	Write CANIDT1, CANIDT2, CANIDT3 and CANIDT4 to the CAN ID value (see IDE bit below)
	//	Write all unused/reserved bits=0
	//	Write CANIDT4.RTRTAG=0 for CAN Data Frame, or =1 for CAN Remote Frame
	// TODO: Why are we clearing these?
	CANIDT4 = 0x00;
	CANIDT3 = 0x00;
	CANIDT2 = 0x00;
	CANIDT1 = 0x00;

	//	Write CANIDM1, CANIDM2, CANIDM3 and CANIDM4 IDMSKn bits to:
	//		=0 for any IDMSKn bit you want to mask (ignore the corresponding CANIDT.IDTn bit value)
	//		=1 for any IDMSKn bit you want to match (use the corresponding CANIDT.IDTn bit value)
	//	Write all unused/reserved bits =0
	//	Write CANIDM4.RTRMSK=1 to match CANIDT4.RTRTAG, or =0 to ignore CANIDT4.RTRTAG
	//		=0 will Rx either CAN Data Frames or CAN Remote Fames
	//		=1 will only Rx the CAN frame type set in CANIDT4.RTRTAG
	//	Write CANIDM4.IDEMSK=1 to match CANCDMOB.IDE, or =0 to ignore CANCDMOB.IDE
	//		=0 will Rx either 11 bit CAN IDs or 29 bit CAN IDs
	//		=1 will only Rx the CAN ID length set in CANCDMOB.IDE

	CANIDM4 = 0x00;
	CANIDM3 = 0x00;
	CANIDM2 = 0x00;
	CANIDM1 = 0x00;

	//	Write CANCDMOB.CONMOBn=10 enable reception for a normal Rx
	//	If CANIDM4.IDEMSK is zero
	//		Also write CANCDMOB.IDE=1 (only use 29 bit IDs in this case)
	//	if CANIDM4.IDEMSK is one
	//		Also write CANCDMOB.IDE=0 for 11 bit IDs, or =1 for 29 bit IDs
	//	Also write CANCDMOB.DLCn to match the number of CANMSG bytes expected to Rx (8 bytes maximum)
	//	Also write CANCDMOB.RPLV=0 for a normal Rx
	//	All four of these CANCDMOB register bit writes are all done together one time only for each MOb task

	CANCDMOB |= _BV(CONMOB1) | ~_BV(CONMOB0) | 0x00;

	return 0;	// Everything went well

}

static uint8_t _canbusGetMOb( uint8_t prio ) {

	uint8_t i;

	// Truncate priority if needed.
	if (prio > MAX_MOb) prio = MAX_MOb;

	//	Find the first available MOb and return it
	for (i = prio; i <= MAX_MOb; i++) {
		if ( !(CANEN2 && _BV(i)) ) {
			return i;	// MOb no. 'i' is available, use that!.
		}
	}

	return 0xFF;		// All MOb:s are busy!
}
