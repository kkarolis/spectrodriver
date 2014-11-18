/*
 * =====================================================================================
 *
 *       Filename:  FakeArduino.c
 *
 *    Description:  Fake arduino implementation
 *
 *        Version:  1.0
 *        Created:  2014.10.28 18:29:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karolis Kalantojus (kkarolis), karolis.kalantojus@gmail.com
 *   Organization:  Vilnius University
 *
 * =====================================================================================
 */
#include <stdint.h>
#include <assert.h>

#include "Pinout.h"
#include "Spectrometer.h"
#include "Stepper.h"
#include "Shutter.h"

#ifdef  TEST
#include "FakeArduino.h"
#else      /* -----  not TEST  ----- */
#include "Arduino.h"
#endif     /* -----  not TEST  ----- */


// Command width in bits should be less than 32
#define CMD_WIDTH 8

void Spectrometer_init(void)
{
        pinMode(BUSY, OUT);
        Stepper_init();
        Shutter_init();
}


uint32_t Spectrometer_parse(uint32_t cmd)
{
        return (cmd & 0xF); 
}

void Spectrometer_busy_set()
{
        digitalWrite(BUSY, HIGH);
}

void Spectrometer_busy_clear()
{
        digitalWrite(BUSY, LOW);
}
