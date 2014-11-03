/*
 * =====================================================================================
 *
 *       Filename:  FakeArduino.h
 *
 *    Description:  Fake arduino header for testing purposes
 *
 *        Version:  1.0
 *        Created:  2014.10.28 16:07:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karolis Kalantojus (kkarolis), karolis.kalantojus@gmail.com
 *   Organization:  Vilnius University
 *
 * =====================================================================================
 */

#ifndef  STEPPER_INC
#define  STEPPER_INC

#include <stdint.h>

#ifdef  TEST
#include "FakeArduino.h"
#else      /* -----  not TEST  ----- */
#include "Arduino.h"
#endif     /* -----  not TEST  ----- */

#define MS1 0
#define MS2 1
#define DIR 2
#define STEP 3
#define RESET 4
#define HOME 5
#define ENABLE 6


// Stepper delay intervals in us
#define STEP_DELAY_US 2

void Stepper_init(void);
void Stepper_step(void);
void Stepper_multistep(uint32_t);
void Stepper_bound_right(void);
void Stepper_bound_left(void);
void Stepper_bound_reset(void);

#endif   /* ----- #ifndef STEPPER_INC  ----- */
