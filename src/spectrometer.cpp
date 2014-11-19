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
// #define ARDUINO_MAIN
#include "Arduino.h"
#include <stdint.h>
#include "Pinout.h"
#include "Stepper.h"

//Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (*func)()) { return 0; }
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
void setup();
void loop();

uint32_t steps = 3; 

void setup() {
        Stepper_init();
}

void loop() {
        Stepper_multistep(steps);
        delayMicroseconds(200);
}

void serialEvent() {}

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
