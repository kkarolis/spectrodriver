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
#include <stdlib.h>
#include "Shutter.h"

#ifdef  TEST
#include "FakeArduino.h"
#else      /* -----  not TEST  ----- */
#include "Arduino.h"
#endif     /* -----  not TEST  ----- */
#include <stdint.h>
#include <assert.h>

static uint32_t open = 0;

void Shutter_init(void)
{
        pinMode(SHUTTER, OUT);
        digitalWrite(SHUTTER, LOW);
}


void Shutter_open(void)
{
        open = 1;
        digitalWrite(SHUTTER, HIGH);
}


void Shutter_close(void)
{
        open = 0;
        digitalWrite(SHUTTER, LOW);
}

/* Probably absolutely useless function */
void Shutter_toggle(void)
{
        open? Shutter_close() : Shutter_open();
}
