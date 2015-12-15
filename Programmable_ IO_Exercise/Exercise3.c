/* 
* Author: Alexander Keidel (22397868)
* Exercise 3: Program LEDs to display binary count starting from 0 (all LED’s off) to 255 (all LED’s on).
*/

#include "GLCD.h" 
#include "LCD_Functions.h" /* Function prototypes for LCD */
#include "LED_Functions.h" /* Function prototypes for LED's */
#include "clock.h"
#include "stm32f10x.h"

#define LEDCOUNT 8 //number of LEDs on the device
#define DELAYLENGTH 2 //delay lengh used in conjunction with the method delayShort() in order to delay for 2 tenths of a second (this is dependent on the system clock setting)

void exercise3(void) {
	int i, l; //loop counters
	
	GLCD_Clear(White);                    /* Clear graphical LCD display        */
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0, 0, __FI, "   < Exercise 3 >   ");
	GLCD_DisplayString(1, 0, __FI, " By Alexander Keidel");
	GLCD_DisplayString(2, 0, __FI, "====================");
	
	for(i = 0; i <= 255; i++){ //loop 255 times to count up
		delayShort(DELAYLENGTH); //delay for 2 tenths of a second
		GPIOB->BRR |= 0x0000FF00; // turn off all LEDs
		for(l = 0; l < LEDCOUNT; l++){ //count through the LEDs and decide to turn them on or off
					if((1 << l) & i){ //if the number (i) has the bit set at the position of 2 to the power of l, i.e. decimal number 8 would have the bit at position "2 to the power of 3" set. This means decimal 8 would look like this: 0000 1000
						  	GPIOB->BSRR |= (1UL << l + 8); //1 cast to UL (unsigned long), because it is a 64 bit register, left shifted l times (number of led) + 8 (this is because of the way the 64 bit register is used, the pins for LED 0 to 7 start after 8)
					}
					//if it is not contained in the number, don't turn the LED on	
		}
	}
}

