/* 
* Author: Chris Nicholas
* Exercise 1: Program LED’s to display the following pattern:
* a)	Turn all LED’s on
* b)	Turn LED 0 off
* c)	Repeat for all other LED’s until all LED’s are off
* d)	Turn LED0 on
* e)	Repeat for all other LED’s until all LED’s are on
* f)	Repeat (b) to (e) 3 times
*/

#include "stm32f10x.h"
#include "GLCD.h" 
#include "LCD_Functions.h" /* Function prototypes for LCD */
#include "LED_Functions.h" /* Function prototypes for LED's */
#include "clock.h"

#define DELAYLENGTH 5

// ALLON references the bitPattern array element 0
// ALLOFF references the bitPattern array element 8
#define ALLON 0
#define AllOFF 8

// Bit pattern mapped to LEDs, 1 = on, 0 = off
char bitPattern[9][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{0, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0}
};



void exercise1(void) {
	int t, u, v; // Loop counters
	char value; // Used when calculating the bit patterns for LED bank
	
	// Initialise LEDs on GPIOB
  RCC->APB2ENR |= (1UL << 3);           /* Enable GPIOB clock                 */

	//The KEIL evaluation board MCBSTM32EXL has 8 green LEDs.
	//These LEDs are connected to MCU's PB8 to PB15 (see the board shematic).

	//The procedure for configuring PB8 to PB15 as output pins:
	//1. PortB's data register ODR defines bits 0 to 15 as output pins.
	//   The following statement resets PB8 to PB15, i.e. LEDs are off.
  	GPIOB->ODR   &= ~0x0000FF00;          /* switch off LEDs                    */
	//2. PortB's configuration register CRH is used to define which PortB
	//   data pins will be configured as output pins. First clear the CRH
	//   register - this sets the pins to input mode.
  	GPIOB->CRH   &= ~0xFFFFFFFF;          /* Configure the GPIO for LEDs        */
	//3. Now configure pins PB8 to PB15 to general purpose output mode (see MCU spec.).
	//   Mode bits set to bin 11 (i.e. output mode) and the configuration bits are set
	//   to bin 00 (i.e. general purpose output).
  	GPIOB->CRH   |=  0x33333333;


	
	GLCD_Clear(White);                    /* Clear graphical LCD display        */
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0, 0, __FI, "   < Exercise 1 >   ");
	GLCD_DisplayString(1, 0, __FI, " By Chris Nicholas  ");
	GLCD_DisplayString(2, 0, __FI, "====================");
	
	// All_LEDs_On(); // Turn all LEDs on
//	GPIOB->BSRR |= (0xFF << 8);

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
