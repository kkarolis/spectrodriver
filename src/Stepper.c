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
#include "Pinout.h"
#include "Stepper.h"
#include <stdint.h>
#include <assert.h>

#ifdef  TEST
#include "FakeArduino.h"
#else      /* -----  not TEST  ----- */
#include "Arduino.h"
#endif     /* -----  not TEST  ----- */

// Stepper delay intervals in us
#define STEP_DELAY_US 2

volatile static uint32_t bound_left;
volatile static uint32_t bound_right;
static int32_t pos;
static int32_t dir;
static StepSize step_size;

struct Routine {
        uint32_t steps_first; /* Before step change */
        uint32_t steps_middle; /* After step change */
        uint32_t steps_last; /* Last step change */
};

/* Here phase is refered to the angle of the rotor */
/* in smallest step size integers. A full rotation takes */
/* 32 smallest steps and each of these is mapped to some */
/* rotor angle. */
/* e.g. 1 - 0.0; 2 - 11.3; 3 - 22.5;...; 32 - 348.8. */
/* At power-on the translator always sets the rotor to 45 degrees */
/* corresponding to number 5. */

/* Keeping the phase in variable is neccesary since step change */
/* can only occur at phases common to all step sizes (5, 13, 21, 29) */
static int32_t phase;


/* Internal module functions */
static void Phase_inc(int32_t step)
{
        phase += step;
        if (phase < 1) {
                phase += 32;
        } else if (phase > 32) {
                phase -= 32;
        }
}


static void i_Stepper_step()
{
        digitalWrite(STEP, HIGH);
        delayMicroseconds(STEP_DELAY_US);
        digitalWrite(STEP, LOW);
        delayMicroseconds(STEP_DELAY_US);
        pos += 1*dir*step_size;
        Phase_inc(1*dir*step_size);
}


static uint32_t calculate_small_steps()
{
        /* Find the interval where phase currently is and */
        /* return the number of EIGHTH steps which have to be */
        /* stepped in order to end up in position where step can be changed */
        int32_t phase_current = Stepper_phase();
        int32_t remainder = (phase_current - 5) % 8;
        if (!remainder) {
                return 0;
        }
        int32_t interval = (phase_current - remainder)/8;
        switch(interval) {
                case 0: /* Interval (5,13) */
                        return (dir == 1)? (13 - phase_current):
                                (phase_current - 5);
                        break;
                case 1: /* (13, 21) */
                        return (dir == 1)? (21 - phase_current):
                                (phase_current - 13);
                        break;
                case 2: /* (21, 29) */
                        return (dir == 1)? (29 - phase_current):
                                (phase_current - 21);
                        break;
                default: /* (29, 5) */
                        if (dir == 1) {
                                return (phase_current < 5)? (5 - phase_current):
                                        (37 - phase_current);
                        } else {
                                return (phase_current < 5)? (phase_current + 3):
                                        (phase_current - 29);
                        }
                        return (dir == 1)? (5 - phase_current):
                                (13 - phase_current);
                        break;
        }
        
}


uint32_t calculate_long_steps(uint32_t steps, uint32_t small_steps)
{
        uint32_t long_steps = 0;
        if (!small_steps) return steps;
        StepSize current_step_size = Stepper_step_size();
        if (current_step_size == FULL) {
                long_steps =  (steps < 1)? 0: steps - 1;
        } else if (current_step_size == HALF) {
                long_steps =  (steps < 2)? 0: steps - 2;
        } else if (current_step_size == QUARTER) {
                long_steps =  (steps < 4)? 0: steps - 4;
        } else { /* EIGHTH */
                long_steps =  (steps < 8)? 0: steps - 8;
        }
        return long_steps;
}


static struct Routine calculate_routine(uint32_t steps)
{
        struct Routine routine;
        uint32_t small_steps = calculate_small_steps();
        uint32_t long_steps = calculate_long_steps(steps, small_steps);
        routine.steps_first = small_steps;
        routine.steps_middle = long_steps;
        routine.steps_last = (!small_steps)? 0: (8 - small_steps);
        return routine;
}


void Stepper_init(void)
{
        pinMode(MS1, OUT);
        digitalWrite(MS1, HIGH);
        pinMode(MS2, OUT);
        digitalWrite(MS2, HIGH);
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
        phase = 5;
        pos = 0;
        dir = 1;
        bound_left = 0;
        bound_right = 0;
        step_size = EIGHTH;
}


void Stepper_step(void)
{
        if (!(bound_left | bound_right)) {
                i_Stepper_step();
        }
}


void Stepper_multistep(uint32_t steps)
{
        struct Routine routine;
        routine = calculate_routine(steps);
        StepSize step_size_small = EIGHTH;
        StepSize step_size_current = Stepper_step_size();
        Stepper_change_step(step_size_small);
        for(uint32_t i = 0; i < routine.steps_first; i++) Stepper_step();
        Stepper_change_step(step_size_current);
        for(uint32_t i = 0; i < routine.steps_middle; i++) Stepper_step();
        Stepper_change_step(step_size_small);
        for(uint32_t i = 0; i < routine.steps_last; i++) Stepper_step();
}


void Stepper_bound_left()
{
        bound_left = 1;
}


void Stepper_bound_right() {
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

void Stepper_home()
{
        Stepper_toggle_dir();
        int32_t steps = Stepper_pos();
        Stepper_multistep(steps);
}

void Stepper_set_home()
{
        pos = 0;
}

void Stepper_set_pos(int32_t position)
{
        pos = position;
}

int32_t Stepper_pos()
{
        return pos;
}

void Stepper_change_dir(int32_t direction)
{
        dir = direction;
}

int32_t Stepper_dir()
{
        return dir;
}

void Stepper_toggle_dir()
{
        dir = -dir;
        if (dir == -1) {
                digitalWrite(DIR, HIGH);
        } else {
                digitalWrite(DIR, LOW);
        }
}

void Stepper_change_step(StepSize size)
{
        step_size = size;
        switch (step_size) {
                case FULL:
                        digitalWrite(MS1, LOW);
                        digitalWrite(MS2, LOW);
                        break;
                case HALF:
                        digitalWrite(MS1, HIGH);
                        digitalWrite(MS2, LOW);
                        break;
                case QUARTER:
                        digitalWrite(MS1, LOW);
                        digitalWrite(MS2, HIGH);
                        break;
                default:
                        digitalWrite(MS1, HIGH);
                        digitalWrite(MS2, HIGH);
                        break;
        }
}

uint32_t Stepper_phase()
{
        return phase;
}

StepSize Stepper_step_size()
{
        return step_size;
}


static void Stepper_return_from_boundary(void)
{
        while(bound_right == 1) {
           i_Stepper_step();
        }
        Stepper_set_home();
}


void Stepper_return_from_right_boundary(void)
{
        Stepper_change_dir(FORWARD);
        Stepper_return_from_boundary();
}


void Stepper_return_from_left_boundary(void)
{
        Stepper_change_dir(BACKWARD);
        Stepper_return_from_boundary();
}
