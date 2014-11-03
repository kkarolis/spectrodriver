/*
 * =====================================================================================
 *
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


void setUp(void)
{
}
 
void tearDown(void)
{
}
 
void test_all_pins_are_input_by_default(void)
{
        TEST_ASSERT_TRUE(modes() == 0x00000000);
}
void test_all_pins_are_low_by_default(void)
{
        TEST_ASSERT_TRUE(states() == 0x00000000);
}

void test_can_set_individual_pin_modes(void)
{
        pinMode(4, OUT);
        TEST_ASSERT_TRUE(get_pinMode(4) == OUT);
}

void test_can_set_individual_pin_states(void)
{
        pinMode(13, OUT);
        digitalWrite(13, HIGH);
        TEST_ASSERT_TRUE(get_pinState(13) == HIGH);
}

void test_can_set_several_pin_modes(void)
{
        pinMode(4, OUT);
        pinMode(13, OUT);
        pinMode(1, IN);
        TEST_ASSERT_TRUE(get_pinMode(4) == OUT);
        TEST_ASSERT_TRUE(get_pinMode(13) == OUT);
        TEST_ASSERT_TRUE(get_pinMode(1) == IN);
}

void test_able_to_reset_pin_hit_count(void)
{
        uint32_t pin = 13;
        pinMode(pin, OUT);
        digitalWrite(pin, HIGH);
        digitalWrite(pin, LOW);
        reset_pin_hits();
        TEST_ASSERT_TRUE(pin_hits(pin) == 0);
}

void test_able_to_check_pin_hit_count(void)
{
        uint32_t pin = 13;
        pinMode(pin, OUT);
        reset_pin_hits();
        digitalWrite(pin, HIGH);
        digitalWrite(pin, LOW);
        digitalWrite(pin, HIGH);
        digitalWrite(pin, LOW);
        uint32_t hits = pin_hits(pin);
        TEST_ASSERT_EQUAL(2, hits);
}
