/******************************************************************************/
/* Blinky.c: LED Flasher                                                      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2010 Keil - An ARM Company. All rights reserved.             */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

//The following include files are pre-defined for you.
//Standard C library definitions
#include <stdio.h>
#include <string.h>
//STM32 MCU specific definitions
#include "stm32f10x.h"                  /* STM32F10x.h definitions            */
#include "GLCD.h"						/* Required for the LCD screen		  */

#include "LED_Functions.h" /* Function prototypes for LED's */
#include "LCD_Functions.h" /* Function prototypes for LCD */
#include "clock.h" /* Function prototypes for clock functions */

#define TRUE		1
#define FALSE		0



#define LED_NUM     8      /* Number of user LEDs  */

extern void exercise1(void);
extern void exercise2(void);


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	int loopCount = 1;
	int i;

	//Following statement sets the timer interrupt frequency
	//The clock rate on this boards MCU is 72 Mhz - this means
	//every second there will be 72 million clocks. So, if use this
	//as the parameter to the function the interrupt rate is going
	//to be every second. If it is reduced to 100 times less then
	//it will do that many clocks in 100 times less time, i.e. 10 msecs.
	//NOTE: We could have chosen to generate a timer interrupt every 1 msec
	//if we wished and that would be quite acceptable in which case we would
	//need to modify the interrupt handler routine in IRQ.c file.
  	SysTick_Config(SystemCoreClock/100);  /* Generate interrupt each 10 ms      */

   	//Here we initialise the LED driver
  	LED_init();                           /* LED Initialization                 */

#ifdef __USE_LCD
	//In order to use the LCD display, the device needs to be
	//properly configured and initialized (refer to GLCD_16bitIF_STM32.c file).
	//This is a complex process and is beyond the scope of this module.
  	GLCD_Init();                          /* Initialize graphical LCD display   */

	//The following functions demonstrate how the LCD display can be used.
	//This is a 240 x 320 pixel colour screen and the pixels can be individually
	//manipulated allowing graphics shapes to be constructed and displayed.
	//This configuration allows 20 characters per line and 10 lines (16x24 pixel characters).
	GLCD_Clear(White);                    /* Clear graphical LCD display        */
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0, 0, __FI, "< Programmable_ IO_Exercise >");
	GLCD_DisplayString(1, 0, __FI, " Hello World!!!  ");
	GLCD_DisplayString(2, 0, __FI, "====================");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Blue);

#endif // __USE_LCD

	//The main body of the program requires a continuous loop which
	//generally executes various functions and monitors various device
	//states. It will be interrupted at regular intervals by the
	//vectored timer interrupt as explained above!
  	while (TRUE) {
			exercise1(); // Do exercise 1 (by Chris Nicholas)
			exercise2(); // Do exercise 2 (by Tom Needham)
		}


		/* PUT MORE LED DISPLAY PATTERNS BELOW */


		//Increment the loop count
		loopCount += 1;
	}
