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
#include <stdint.h>

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


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  Serial.print("sizeof(byte)="); Serial.println(sizeof(byte));
  Serial.print("sizeof(char)="); Serial.println(sizeof(char));
  Serial.print("sizeof(short)="); Serial.println(sizeof(short));
  Serial.print("sizeof(int)="); Serial.println(sizeof(int));
  Serial.print("sizeof(long)="); Serial.println(sizeof(long));
  Serial.print("sizeof(long long)="); Serial.println(sizeof(long long));
  Serial.print("sizeof(bool)="); Serial.println(sizeof(bool));
  Serial.print("sizeof(boolean)="); Serial.println(sizeof(boolean));
  Serial.print("sizeof(float)="); Serial.println(sizeof(float));
  Serial.print("sizeof(double)="); Serial.println(sizeof(double));
  Serial.print("sizeof(int8_t)="); Serial.println(sizeof(int8_t));
  Serial.print("sizeof(int16_t)="); Serial.println(sizeof(int16_t));
  Serial.print("sizeof(int32_t)="); Serial.println(sizeof(int32_t));
  Serial.print("sizeof(int64_t)="); Serial.println(sizeof(int64_t));
  Serial.print("sizeof(uint8_t)="); Serial.println(sizeof(uint8_t));
  Serial.print("sizeof(uint16_t)="); Serial.println(sizeof(uint16_t));
  Serial.print("sizeof(uint32_t)="); Serial.println(sizeof(uint32_t));
  Serial.print("sizeof(uint64_t)="); Serial.println(sizeof(uint64_t));
  Serial.print("sizeof(char*)="); Serial.println(sizeof(char*));
  Serial.print("sizeof(int*)="); Serial.println(sizeof(int*));
  Serial.print("sizeof(long*)="); Serial.println(sizeof(long*));
  Serial.print("sizeof(float*)="); Serial.println(sizeof(float*));
  Serial.print("sizeof(double*)="); Serial.println(sizeof(double*));
  Serial.print("sizeof(void*)="); Serial.println(sizeof(void*));
  Serial.println();
  delay(5000);
}

// void loop() {
  // // print the string when a newline arrives:
  // if (stringComplete) {
    // Serial.println(inputString);
    // // clear the string:
    // inputString = "";
    // stringComplete = false;
  // }
// }

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

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
