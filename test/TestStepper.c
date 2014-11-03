/* =====================================================================================
 *       Filename:  TestDelaySetFunction.c
 *
 *    Description:  Test the simple function
 *
 *        Version:  1.0
 *        Created:  2014.10.23 23:11:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "unity.h"
#include <stdint.h>
#include "FakeArduino.h"
#include "Stepper.h"


void setUp(void)
{
        reset_pin_hits();
        Stepper_init();
}


void tearDown(void)
{
        Stepper_bound_reset();
}
 

void test_stepper_initializes_pins_as_outputs(void)
{
        TEST_ASSERT_EQUAL(get_pinMode(MS1), OUT);
        TEST_ASSERT_EQUAL(get_pinMode(MS2), OUT);
        TEST_ASSERT_EQUAL(get_pinMode(DIR), OUT);
        TEST_ASSERT_EQUAL(get_pinMode(STEP), OUT);
        TEST_ASSERT_EQUAL(get_pinMode(RESET), OUT);
        TEST_ASSERT_EQUAL(get_pinMode(HOME), OUT);
        TEST_ASSERT_EQUAL(get_pinMode(ENABLE), OUT);
}


void test_stepper_is_able_to_step(void)
{
        Stepper_step();
        Stepper_step();
        Stepper_step();
        TEST_ASSERT_EQUAL(3, pin_hits(STEP));
}


void test_stepper_is_able_to_step_multiple_steps(void)
{
        uint32_t steps = 12;
        Stepper_multistep(steps);
        TEST_ASSERT_EQUAL(steps, pin_hits(STEP));
}

void test_stepper_does_not_step_when_boundary_is_encountered(void)
{
        Stepper_step();
        Stepper_step();
        Stepper_step();
        Stepper_bound_left();
        Stepper_step();
        TEST_ASSERT_EQUAL(3, pin_hits(STEP));
}


void test_multistep_after_boundary_does_not_work(void)
{
        uint32_t steps = 5;
        Stepper_multistep(steps);
        Stepper_bound_right();
        Stepper_multistep(steps);
        TEST_ASSERT_EQUAL(5, pin_hits(STEP));
}
