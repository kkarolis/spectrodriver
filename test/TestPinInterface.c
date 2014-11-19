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
        reset_pin_hits();
        reset_pin_toggles();
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
        pinMode(4, OUTPUT);
        TEST_ASSERT_TRUE(get_pinMode(4) == OUTPUT);
}

void test_can_set_individual_pin_states(void)
{
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        TEST_ASSERT_TRUE(get_pinState(13) == HIGH);
}

void test_can_set_several_pin_modes(void)
{
        pinMode(4, OUTPUT);
        pinMode(13, OUTPUT);
        pinMode(1, IN);
        TEST_ASSERT_TRUE(get_pinMode(4) == OUTPUT);
        TEST_ASSERT_TRUE(get_pinMode(13) == OUTPUT);
        TEST_ASSERT_TRUE(get_pinMode(1) == IN);
}

void test_able_to_reset_pin_hit_count(void)
{
        uint32_t pin = 13;
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);
        digitalWrite(pin, LOW);
        reset_pin_hits();
        TEST_ASSERT_TRUE(pin_hits(pin) == 0);
}

void test_able_to_check_pin_hit_count(void)
{
        uint32_t pin = 13;
        pinMode(pin, OUTPUT);
        reset_pin_hits();
        digitalWrite(pin, HIGH);
        digitalWrite(pin, LOW);
        digitalWrite(pin, HIGH);
        digitalWrite(pin, LOW);
        uint32_t hits = pin_hits(pin);
        TEST_ASSERT_EQUAL(2, hits);
}

void test_able_to_check_pin_toggles(void) {
        uint32_t pin = 13;
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        digitalWrite(pin, HIGH);
        digitalWrite(pin, HIGH);
        digitalWrite(pin, LOW);
        uint32_t toggles = pin_toggles(pin);
        TEST_ASSERT_EQUAL(2, toggles);

}

void test_able_to_reset_pin_toggles(void) {
        uint32_t pin = 13;
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        digitalWrite(pin, HIGH);
        digitalWrite(pin, HIGH);
        digitalWrite(pin, LOW);
        reset_pin_toggles();
        uint32_t toggles = pin_toggles(pin);
        TEST_ASSERT_EQUAL(0, toggles);
}
