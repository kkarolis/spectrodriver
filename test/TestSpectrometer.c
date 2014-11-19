/*
 * =====================================================================================
 *
 *       Filename:  TestSpectrometer.c
 *
 *    Description:  j
 *
 *        Version:  1.0
 *        Created:  2014.11.19 07:46:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karolis Kalantojus (kkarolis), karolis.kalantojus@gmail.com
 *   Organization:  Vilnius University
 *
 * =====================================================================================
 */
#include <stdlib.h>
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
        TEST_ASSERT_TRUE(get_pinMode(MS1) == OUTPUT);
        TEST_ASSERT_TRUE(get_pinState(MS1) == HIGH);
        TEST_ASSERT_TRUE(get_pinMode(MS2) == OUTPUT);
        TEST_ASSERT_TRUE(get_pinState(MS2) == HIGH);
        TEST_ASSERT_TRUE(get_pinMode(DIR) == OUTPUT);
        TEST_ASSERT_TRUE(get_pinState(DIR) == LOW);
        TEST_ASSERT_TRUE(get_pinMode(STEP) == OUTPUT);
        TEST_ASSERT_TRUE(get_pinState(STEP) == LOW);
        TEST_ASSERT_TRUE(get_pinMode(HOME) == OUTPUT);
        TEST_ASSERT_TRUE(get_pinState(HOME) == LOW);
        TEST_ASSERT_TRUE(get_pinMode(BUSY) == OUTPUT);
        TEST_ASSERT_TRUE(get_pinState(BUSY) == LOW);
}

void test_spectrometer_command_parsing_works_correctly(void) {
        uint32_t cmd = 0xFFFFFFF1;
        TEST_ASSERT_TRUE(Spectrometer_parse(cmd) == 1);
}

void test_spectrometer_can_set_and_clear_busy_flag(void) {
        Spectrometer_busy_set();
        TEST_ASSERT_TRUE(get_pinState(BUSY) == HIGH);
        Spectrometer_busy_clear();
        TEST_ASSERT_TRUE(get_pinState(BUSY) == LOW);
}
