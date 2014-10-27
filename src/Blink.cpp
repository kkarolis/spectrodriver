/*
 * =====================================================================================
 *
 *       Filename:  Blink.cpp
 *
 *    Description:  Blink LED with delay set by a simple function
 *
 *        Version:  1.0
 *        Created:  2014.10.07 07:43:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#define ARDUINO_MAIN
#include "Arduino.h"
#include "DelaySetFunction.h"

/*
 * Cortex-M3 Systick IT handler
 */
/*
extern void SysTick_Handler( void )
{
  // Increment tick count each ms
  TimeTick_Increment() ;
}
*/

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(incrementDelay(1000));              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(incrementDelay(1000));              // wait for a second
}
/*
 * \brief Main entry point of Arduino application
 */

int main( void )
{
	init();

	initVariant();

	delay(1);

#if defined(USBCON)
	USBDevice.attach();
#endif

	setup();

	for (;;)
	{
		loop();
		if (serialEventRun) serialEventRun();
	}

	return 0;
}
