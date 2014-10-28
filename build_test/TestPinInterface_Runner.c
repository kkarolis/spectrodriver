/* AUTOGENERATED FILE. DO NOT EDIT. */

//=======Test Runner Used To Run Each Test Below=====
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT() && !TEST_IS_IGNORED) \
  { \
    tearDown(); \
  } \
  UnityConcludeTest(); \
}

//=======Automagically Detected Files To Include=====
#include "unity.h"
#include <setjmp.h>
#include <stdio.h>
#include "FakeArduino.h"
#include <stdint.h>

//=======External Functions This Runner Calls=====
extern void setUp(void);
extern void tearDown(void);
extern void test_all_pins_are_input_by_default(void);
extern void test_all_pins_are_low_by_default(void);
extern void test_can_set_individual_pin_modes(void);
extern void test_can_set_individual_pin_states(void);
extern void test_can_set_several_pin_modes(void);


//=======Test Reset Option=====
void resetTest()
{
  tearDown();
  setUp();
}


//=======MAIN=====
int main(void)
{
  UnityBegin("/home/karolis/my_files/projects/vu_work/spectrometer_driver/test/TestPinInterface.c");
  RUN_TEST(test_all_pins_are_input_by_default, 31);
  RUN_TEST(test_all_pins_are_low_by_default, 35);
  RUN_TEST(test_can_set_individual_pin_modes, 40);
  RUN_TEST(test_can_set_individual_pin_states, 46);
  RUN_TEST(test_can_set_several_pin_modes, 53);

  return (UnityEnd());
}
