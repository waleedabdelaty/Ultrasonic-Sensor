/*
 * ultrasonic.c
 *
 *  Created on: Oct 15, 2021
 *      Author: TOSHIBA PC
 */

#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include "util/delay.h"



uint32 timer_value;  //global variable for time of pulse
uint8 sensor_work=0; // global variable to detect starting of calculate distance
uint8 g_edgeCount = 0;


/*
 * Description
 *Initialize the ICU driver as required.
 *Setup the ICU call back function.
 *Setup the direction for the trigger pin as output pin through the GPIO driver.
 */

void Ultrasonic_init(void)
{

	Icu_ConfigType Icu_Config = {F_CPU_8,RISING};
	Icu_init(&Icu_Config);

	Icu_setCallBack(Ultrasonic_edgeProcessing);

	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);

}



/*
 * Description: Send the Trigger pulse to the ultrasonic.
 */


void Ultrasonic_Trigger(void)
{
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);


}



/*
 Description
 Send the trigger pulse by using Ultrasonic_Trigger function.
 Start the measurements by the ICU from this moment.
 */



uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	sensor_work=1;
	return (uint16)((timer_value)/57.5);

}





void Ultrasonic_edgeProcessing(void)
{
	if(sensor_work)
	{
		g_edgeCount++;
			if(g_edgeCount == 1)
			{
				/*
				 * Clear the timer counter register to start measurements from the
				 * first detected rising edge
				 */
				Icu_clearTimerValue();
				/* Detect falling edge */
				Icu_setEdgeDetectionType(FALLING);
			}
			else if(g_edgeCount == 2)
			{
				/* Store the High time value */
				timer_value = Icu_getInputCaptureValue();
				/* Detect rising edge */
				Icu_setEdgeDetectionType(RISING);
				g_edgeCount=0;
			}
	}

}

