/*
 * ultrasonic.h
 *
 *  Created on: Oct 15, 2021
 *      Author: TOSHIBA PC
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"
#include "common_macros.h"



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);



#endif /* ULTRASONIC_H_ */
