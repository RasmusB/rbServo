/*
 * canbus.h
 *
 *  Created on: Oct 30, 2012
 *      Author: rasmus
 */

#ifndef CANBUS_H_
#define CANBUS_H_

extern uint8_t canbusID;
extern uint8_t canbusDataBuffer[8];

void canbusInit( void );
uint8_t canbusTXsetup( uint16_t messageID, uint8_t messageDLC, uint8_t prio );
uint8_t canbusRXsetup( uint8_t prio );

#endif /* CANBUS_H_ */
