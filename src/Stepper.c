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
#include "Stepper.h"

#ifdef  TEST
#include "FakeArduino.h"
#else      /* -----  not TEST  ----- */
#include "Arduino.h"
#endif     /* -----  not TEST  ----- */
#include <stdint.h>
#include <assert.h>

volatile static uint32_t bound_left = 0;
volatile static uint32_t bound_right = 0;


void Stepper_init(void)
{
        pinMode(MS1, OUT);
        digitalWrite(MS1, LOW);
        pinMode(MS2, OUT);
        digitalWrite(MS2, LOW);
        pinMode(DIR, OUT);
        digitalWrite(DIR, LOW);
        pinMode(STEP, OUT);
        digitalWrite(STEP, LOW);
        pinMode(RESET, OUT);
        digitalWrite(RESET, LOW);
        pinMode(HOME, OUT);
        digitalWrite(HOME, LOW);
        pinMode(ENABLE, OUT);
        digitalWrite(ENABLE, LOW);
}


void Stepper_step(void)
{
        if (!(bound_left | bound_right)) {
                digitalWrite(STEP, HIGH);
                delayMicroseconds(STEP_DELAY_US);
                digitalWrite(STEP, LOW);
                delayMicroseconds(STEP_DELAY_US);
        }
}


void Stepper_multistep(uint32_t steps)
{
        for(uint32_t i = 0; i < steps; i++) Stepper_step();
}


void Stepper_bound_left()
{
        bound_left = 1;
}


void Stepper_bound_right()
{
        bound_right = 1; 
}


void Stepper_bound_reset()
{
        if (bound_left) {
                bound_left = 0;
        } else {
                bound_right = 0;
        }
}
