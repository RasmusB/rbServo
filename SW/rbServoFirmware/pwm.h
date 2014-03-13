/*
 * pwm.h
 *
 *  Created on: Nov 9, 2012
 *      Author: rasmus
 */

#ifndef PWM_H_
#define PWM_H_

extern volatile uint8_t secondTick;

void pwmInit ( void );
void pwmSetDutyCycle(uint16_t newDutyCycle);

#endif /* PWM_H_ */
