/*
 * sensors.h
 *
 *  Created on: Nov 9, 2012
 *      Author: rasmus
 */

#ifndef SENSORS_H_
#define SENSORS_H_

void sensorInit( void );
void adcInit( void );
uint16_t sensorVBattGetRaw(void);
uint16_t sensorVBattGetValue(void);
uint16_t sensorPotGetRaw(void);
int16_t sensorPotGetValue(void);

#endif /* SENSORS_H_ */
