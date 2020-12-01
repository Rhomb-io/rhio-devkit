#include "test_state-machine.h"

#include <Arduino.h>
#include <unity.h>

#include "rhio-state-machine.h"

namespace state_test {

StateMachine states(5);

#define F1 0x01
#define F2 0x02
#define F3 0x03
#define F4 0x04
#define F5 0x05

void test_state_running_1(void) { TEST_ASSERT_EQUAL(F1, states.getCurrent()); }

void test_state_running_2(void) { TEST_ASSERT_EQUAL(F2, states.getCurrent()); }

void test_state_running_3(void) { TEST_ASSERT_EQUAL(F3, states.getCurrent()); }

void test_state_running_4(void) { TEST_ASSERT_EQUAL(F4, states.getCurrent()); }

void test_state_running_5(void) { TEST_ASSERT_EQUAL(F5, states.getCurrent()); }

int _prevState = -1;
int _newState = -1;
void test_state_on_change(void) {
  static int counter = 1;
  switch (counter) {
    case 1:
      TEST_ASSERT_EQUAL(1, _prevState);
      TEST_ASSERT_EQUAL(2, _newState);
      break;
    case 2:
      TEST_ASSERT_EQUAL(2, _prevState);
      TEST_ASSERT_EQUAL(3, _newState);
      break;
    case 3:
      TEST_ASSERT_EQUAL(3, _prevState);
      TEST_ASSERT_EQUAL(4, _newState);
      break;
    case 4:
      TEST_ASSERT_EQUAL(4, _prevState);
      TEST_ASSERT_EQUAL(5, _newState);
      break;
    case 5:
      TEST_ASSERT_EQUAL(5, _prevState);
      TEST_ASSERT_EQUAL(1, _newState);
      break;
  }

  counter++;
}

void onChange(int prevState, int newState) {
  _prevState = prevState;
  _newState = newState;
  RUN_TEST(test_state_on_change);
}

stateCallback f1() {
  RUN_TEST(test_state_running_1);
  states.set(F2);
}
stateCallback f2() {
  RUN_TEST(test_state_running_2);
  states.set(F3);
}
stateCallback f3() {
  RUN_TEST(test_state_running_3);
  states.set(F4);
}
stateCallback f4() {
  RUN_TEST(test_state_running_4);
  states.set(F5);
}
stateCallback f5() {
  RUN_TEST(test_state_running_5);
  states.set(F1);
}

void test_state_add_when_full(void) {
  bool result = states.add(F1, f1);
  TEST_ASSERT_EQUAL(false, result);
}

void test_state_add_when_not_full(void) {
  bool result = states.add(F1, f1);
  TEST_ASSERT_EQUAL(true, result);
}

void test_state_remove_by_name(void) {
  bool result = states.removeByName(F1);
  TEST_ASSERT_EQUAL(true, result);
}

void test_state_unknow_name(void) {
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
  states.onChange(onChange);

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
  RUN_TEST(test_state_add_when_full);
  RUN_TEST(test_state_remove_by_name);
  RUN_TEST(test_state_add_when_not_full);
  RUN_TEST(test_state_unknow_name);

  // part 3 (retry part 1)
  steps = 5;
  while (steps--) {
    states.run();
  }
  states.run();  // last time, check pass from 5 to 1
}

}  // namespace state_test
