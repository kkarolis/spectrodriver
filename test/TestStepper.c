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
        Stepper_init();
        reset_pin_hits();
        reset_pin_toggles();
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

void test_long_steps_are_calculated_correctly(void)
{
        StepSize step_size = EIGHTH;
        Stepper_change_step(step_size);
        uint32_t steps = 5;
        uint32_t long_steps = 0;
        long_steps = calculate_long_steps(steps, 1);
        TEST_ASSERT_EQUAL(0, long_steps);
}

void test_stepper_can_return_home(void) {
        uint32_t steps = 2000;
        Stepper_multistep(steps);
        Stepper_home();
        TEST_ASSERT_EQUAL(0, Stepper_pos());
        TEST_ASSERT_EQUAL(4000, pin_hits(STEP));
}


void test_stepper_decrements_pos_on_dir_change(void)
{
        uint32_t steps = 2000;
        Stepper_multistep(steps);
        Stepper_toggle_dir();
        Stepper_multistep(steps);
        TEST_ASSERT_EQUAL(0, Stepper_pos());
}


void test_stepper_is_able_to_change_dir(void) {
        TEST_ASSERT_EQUAL(FORWARD, Stepper_dir());
        Stepper_toggle_dir();
        TEST_ASSERT_EQUAL(1, pin_toggles(DIR));
        TEST_ASSERT_EQUAL(BACKWARD, Stepper_dir());
        Stepper_toggle_dir();
        TEST_ASSERT_EQUAL(FORWARD, Stepper_dir());
}


void test_stepper_can_return_relative_position(void) {
        uint32_t steps = 1000;
        Stepper_multistep(steps);
        TEST_ASSERT_EQUAL(1000, Stepper_pos());
}


void test_stepper_increments_phase_on_steps(void) {
        uint32_t steps = 10;
        Stepper_multistep(steps);
        TEST_ASSERT_EQUAL(15, Stepper_phase());
}


void test_stepper_can_return_relative_position_in_other_step_sizes(void) {
        uint32_t steps = 100;
        int32_t check_pos = 0;
        StepSize step_size_full = FULL;
        StepSize step_size_half = HALF;
        StepSize step_size_quarter = QUARTER;
        StepSize step_size_eighth = EIGHTH;
        Stepper_change_step(step_size_full);
        Stepper_multistep(steps);
        check_pos = steps*8;
        TEST_ASSERT_EQUAL(check_pos, Stepper_pos());
        Stepper_change_step(step_size_half);
        Stepper_multistep(steps);
        check_pos += steps*4;
        TEST_ASSERT_EQUAL(check_pos, Stepper_pos());
        Stepper_change_step(step_size_quarter);
        Stepper_multistep(steps);
        check_pos += steps*2;
        TEST_ASSERT_EQUAL(check_pos, Stepper_pos());
        Stepper_change_step(step_size_eighth);
        Stepper_multistep(steps);
        check_pos += steps;
        TEST_ASSERT_EQUAL(check_pos, Stepper_pos());
}

void test_stepper_sets_correct_step_pins(void)
{
        StepSize step_size_full = FULL;
        StepSize step_size_half = HALF;
        StepSize step_size_quarter = QUARTER;
        StepSize step_size_eighth = EIGHTH;
        Stepper_change_step(step_size_full);
        TEST_ASSERT_EQUAL(LOW, get_pinState(MS1));
        TEST_ASSERT_EQUAL(LOW, get_pinState(MS2));
        Stepper_change_step(step_size_half);
        TEST_ASSERT_EQUAL(HIGH, get_pinState(MS1));
        TEST_ASSERT_EQUAL(LOW, get_pinState(MS2));
        Stepper_change_step(step_size_quarter);
        TEST_ASSERT_EQUAL(LOW, get_pinState(MS1));
        TEST_ASSERT_EQUAL(HIGH, get_pinState(MS2));
        Stepper_change_step(step_size_eighth);
        TEST_ASSERT_EQUAL(HIGH, get_pinState(MS1));
        TEST_ASSERT_EQUAL(HIGH, get_pinState(MS2));
}

void test_stepper_ends_up_on_correct_phase_on_startup(void) {
        TEST_ASSERT_EQUAL(5, Stepper_phase());
}


void test_stepper_changes_step_at_correct_phase(void) {
        /* Move stepper out of phase */
        Stepper_step();
        /* Change step size */
        StepSize step_size_half = HALF;
        uint32_t steps = 3;
        Stepper_change_step(step_size_half);
        Stepper_multistep(steps);
        TEST_ASSERT_EQUAL(1 + steps*step_size_half, Stepper_pos());
        TEST_ASSERT_EQUAL(1 + 9, pin_hits(STEP));
}


void test_stepper_can_get_step_size(void) {
        StepSize step_size_half = HALF;
        Stepper_change_step(step_size_half);
        TEST_ASSERT_EQUAL(step_size_half, Stepper_step_size());
}


void test_stepper_can_set_home(void) {
        uint32_t steps = 100;
        Stepper_multistep(steps);
        Stepper_set_home();
        Stepper_multistep(steps);
        Stepper_home();
        TEST_ASSERT_EQUAL(0, Stepper_pos());
        TEST_ASSERT_EQUAL(300, pin_hits(STEP));
}


void test_phase_is_circular(void) {
        uint32_t steps = 30;
        Stepper_multistep(steps);
        TEST_ASSERT_EQUAL(5 + steps - 32, Stepper_phase());
}

void test_stepper_is_able_to_change_dir_explicitly(void) 
{
        Stepper_change_dir(BACKWARD);
        TEST_ASSERT_EQUAL(BACKWARD, Stepper_dir());
        Stepper_change_dir(FORWARD);
        TEST_ASSERT_EQUAL(FORWARD, Stepper_dir());
}
