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
#include "DelaySetFunction.h"
 
void setUp(void)
{
}
 
void tearDown(void)
{
}
 
void test_DelaySetFunctionShouldBeCorrect(void)
{
    TEST_ASSERT_EQUAL_INT(2000, incrementDelay(1000));
}
