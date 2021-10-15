/*
 * main.c
 *
 *  Created on: Oct 15, 2021
 *      Author: TOSHIBA PC
 */


#include "ultrasonic.h"
#include "lcd.h"
#include <avr/io.h> /* To use the SREG register */
#include "util/delay.h"




int main(void)
{
	uint16 distance ;
	LCD_init();
	Ultrasonic_init();

	/* Enable Global Interrupt I-Bit */
		SREG |= (1<<7);


	while(1)
	{
		distance=Ultrasonic_readDistance();

		LCD_moveCursor(0, 1);
				LCD_displayString("Distance= ");
				if(distance>100)
				{
					LCD_intgerToString(distance);
				}
				else
				{
					LCD_intgerToString(distance);
					LCD_displayCharacter(' ');
				}
				LCD_displayString("cm");
				_delay_ms(100);


	}

	return 0;

}
