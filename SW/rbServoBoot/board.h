/*
 * board.h
 *
 *  Created on: Nov 8, 2012
 *      Author: rasmus
 */

#ifndef BOARD_H_
#define BOARD_H_

void boardInit ( void );

void redLEDon ( void );

void redLEDoff ( void );

void redLEDtoggle ( void );

void redLEDpwm ( uint8_t dutyCycle );

#endif /* BOARD_H_ */
