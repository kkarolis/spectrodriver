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
#include "Shutter.h"


void setUp(void)
{
        Shutter_init();
}


void tearDown(void)
{
}

void test_shutter_init_works(void)
{
        Shutter_init();
        TEST_ASSERT_EQUAL(get_pinMode(SHUTTER), OUTPUT);
        TEST_ASSERT_EQUAL(get_pinState(SHUTTER), LOW);
}


void test_shutter_open(void)
{
        Shutter_open();
        TEST_ASSERT_EQUAL(get_pinState(SHUTTER), HIGH);
}


void test_shutter_close(void)
{
        Shutter_open();
        Shutter_close();
        TEST_ASSERT_EQUAL(get_pinState(SHUTTER), LOW);
}

void test_shutter_toggle(void)
{
        Shutter_open();
        Shutter_toggle();
        TEST_ASSERT_EQUAL(get_pinState(SHUTTER), LOW);
        Shutter_toggle();
        TEST_ASSERT_EQUAL(get_pinState(SHUTTER), HIGH);
}
