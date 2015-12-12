/* 
* Author: Tom Needham (22416714)
* Exercise 2: Program LED’s to display the following pattern
*
* a)	Turn all LED’s off
* b)	Turn LED’s 0,1,2 on
* c)	Turn LED’s 0,1,2 off
* d)	Turn LED’s 3,4,5 on
* e)	Turn LED’s 3,4,5 off
* f)	Turn LED’s 6,7,0 on
* g)	Turn LED’s 6,7,0 off
* h)	Turn LED’s 1,2,3 on
* i)	Turn LED’s 1,2,3 off
* j)	Repeat pattern
*
*/
#include "GLCD.h"						/* Required for the LCD screen		  */
#include "LED_Functions.h" /* Function prototypes for LED's */
#include "LCD_Functions.h"
#include "clock.h"
#include "stm32f10x.h"

#define DELAYLENGTH 5

void exercise2(void) {
	int t = 0;
	int u = 0;
	int v = 0;
	int value = 0;
	char bitPattern[9][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
};
	GLCD_Clear(White);                    /* Clear graphical LCD display        */
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0, 0, __FI, "   < Exercise 2>    ");
	GLCD_DisplayString(1, 0, __FI, " By Thomas Needham  ");
	GLCD_DisplayString(2, 0, __FI, "====================");
	for(t = 0; t < 3; t++) { // Main outer loop
		for(u = 0; u < 9; u++) {
			value = 0;
			
			for(v = 0; v < 8; v++) { // translate the bitPattern array into binary value.
				value |= bitPattern[u][v] << v;		
			}
			
			GPIOB->BRR |= 0x0000FF00;  // Clear LEDs
			GPIOB->BSRR |= value << 8; // Set ON required LEDs
			
			delayShort(DELAYLENGTH); 
			
		}	
		
		for(u = 8; u >= 0; u--) {
			value = 0;
			
			for(v = 0; v < 8; v++) { // translate the bitPattern array into binary value.
				value |= bitPattern[u][v] << v;		
			}
			
			GPIOB->BRR |= 0x0000FF00;  // Clear LEDs
			GPIOB->BSRR |= value << 8; // Set ON required LEDs
			
			delayShort(DELAYLENGTH); 
			
		}	

	}	
}
