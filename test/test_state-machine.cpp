#include "test_state-machine.h"

#include <Arduino.h>
#include <unity.h>

#include "rhio-state-machine.h"

namespace state {

StateMachine states(5);

#define F1 0x01
#define F2 0x02
#define F3 0x03
#define F4 0x04
#define F5 0x05

void test_running_state_1(void) { TEST_ASSERT_EQUAL(F1, states.getCurrent()); }

void test_running_state_2(void) { TEST_ASSERT_EQUAL(F2, states.getCurrent()); }

void test_running_state_3(void) { TEST_ASSERT_EQUAL(F3, states.getCurrent()); }

void test_running_state_4(void) { TEST_ASSERT_EQUAL(F4, states.getCurrent()); }

void test_running_state_5(void) { TEST_ASSERT_EQUAL(F5, states.getCurrent()); }

void f1() {
  RUN_TEST(test_running_state_1);
  states.set(F2);
}
void f2() {
  RUN_TEST(test_running_state_2);
  states.set(F3);
}
void f3() {
  RUN_TEST(test_running_state_3);
  states.set(F4);
}
void f4() {
  RUN_TEST(test_running_state_4);
  states.set(F5);
}
void f5() {
  RUN_TEST(test_running_state_5);
  states.set(F1);
}

void test_add_when_is_full(void) {
  bool result = states.add(F1, f1);
  TEST_ASSERT_EQUAL(false, result);
}

void test_add_when_is_not_full(void) {
  bool result = states.add(F1, f1);
  TEST_ASSERT_EQUAL(true, result);
}

void test_remove_by_name(void) {
  bool result = states.removeByName(F1);
  TEST_ASSERT_EQUAL(true, result);
}

void test_unknow_state_name(void) {
  int result = states.set(0x06);
  TEST_ASSERT_EQUAL(-1, result);
}

void init() {
  states.add(F1, f1);
  states.add(F2, f2);
  states.add(F3, f3);
  states.add(F4, f4);
  states.add(F5, f5);
  states.set(F1);
  run();
}

void run() {
  // part 1
  int steps = 5;
  while (steps--) {
    states.run();
  }
  states.run();  // last time, check pass from 5 to 1

  // part 2
  RUN_TEST(test_add_when_is_full);
  RUN_TEST(test_remove_by_name);
  RUN_TEST(test_add_when_is_not_full);
  RUN_TEST(test_unknow_state_name);

  // part 3 (retry part 1)
  steps = 5;
  while (steps--) {
    states.run();
  }
  states.run();  // last time, check pass from 5 to 1
}

}  // namespace state
