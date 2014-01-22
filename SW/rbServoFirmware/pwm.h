/*
 * pwm.h
 *
 *  Created on: Nov 9, 2012
 *      Author: rasmus
 */

#ifndef PWM_H_
#define PWM_H_

void pwmInit ( void );
void pwmSetDutyCycle (uint8_t pwmChannel, uint8_t pwmDutyCycle);

#endif /* PWM_H_ */
