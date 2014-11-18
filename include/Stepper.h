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
#include "Pinout.h"

#define FORWARD 1
#define BACKWARD -1

#ifdef  TEST
#include "FakeArduino.h"
#else      /* -----  not TEST  ----- */
#include "Arduino.h"
#endif     /* -----  not TEST  ----- */

typedef enum {
        FULL=8,
        HALF=4,
        QUARTER=2,
        EIGHTH=1
} StepSize;


uint32_t calculate_long_steps(uint32_t, uint32_t);
void Stepper_init(void);
void Stepper_step(void);
void Stepper_multistep(uint32_t);
void Stepper_bound_right(void);
void Stepper_bound_left(void);
void Stepper_bound_reset(void);
void Stepper_set_pos(int32_t);
int32_t Stepper_pos(void);
int32_t Stepper_dir(void);
void Stepper_change_dir(int32_t);
void Stepper_toggle_dir(void);
void Stepper_change_step(StepSize);
uint32_t Stepper_phase(void);
void Stepper_home(void);
void Stepper_set_home(void);
void Stepper_change_dir(int32_t);
StepSize Stepper_step_size(void);

#endif   /* ----- #ifndef STEPPER_INC  ----- */
