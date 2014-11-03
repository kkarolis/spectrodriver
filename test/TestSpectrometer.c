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
#include "Spectrometer.h"


void setUp(void)
{
}
 
void tearDown(void)
{
}
 
void test_spectrometr_initializes_needed_pins_to_output(void) {
        Spectrometer_init();
        TEST_ASSERT_TRUE(get_pinMode(MS1) == OUT);
        TEST_ASSERT_TRUE(get_pinMode(MS2) == OUT);
        TEST_ASSERT_TRUE(get_pinMode(DIR) == OUT);
        TEST_ASSERT_TRUE(get_pinMode(STEP) == OUT);
        TEST_ASSERT_TRUE(get_pinMode(HOME) == OUT);
}

void test_spectrometer_command_parsing_works_correctly(void) {
        uint32_t cmd = 0xFFFFFFF1;
        TEST_ASSERT_TRUE(Spectrometer_parse(cmd) == 1);
}
