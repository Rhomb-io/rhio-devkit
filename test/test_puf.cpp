#include "test_puf.h"

#include <Arduino.h>
#include <unity.h>

#include "rhio-puf.h"

namespace puf_test {

Puf puf;

int counter = 0;
char err = 0;

pufcb ev1(int param) {
  counter = 1;
  TEST_ASSERT_EQUAL(1, counter);
  err = puf.emit(0x02, 2);
  TEST_ASSERT_EQUAL(err, 0);
  return 0;
}

pufcb ev2(int param) {
  counter += param;
  TEST_ASSERT_EQUAL(3, counter);
  err = puf.emit(0x03, 3);
  TEST_ASSERT_EQUAL(err, 0);
  return 0;
}

pufcb ev3(int param) {
  counter += param;
  TEST_ASSERT_EQUAL(6, counter);
  err = puf.emit(0x04, 6);
  TEST_ASSERT_EQUAL(err, 0);
  return 0;
}

pufcb ev4(int param) {
  counter += param;
  TEST_ASSERT_EQUAL(12, counter);
  err = puf.emit(0x05, 12);
  TEST_ASSERT_EQUAL(err, 0);
  return 0;
}

pufcb ev5(int param) {
  counter += param;
  TEST_ASSERT_EQUAL(24, counter);
  return 0;
}

// err_ev2 should not get called because err_ev1 returns an error (1)
pufcb err_ev1(int param) { return 1; }
pufcb err_ev2(int param) {
  TEST_ASSERT_EQUAL(true, false);
  return 0;
}

void test_puf_run_events_ordered() { puf.emit(0x01, 0); }
void test_puf_stop_on_error() {
  char err = puf.emit(0x06, 0);
  TEST_ASSERT_EQUAL(1, err);
}

void init() {
  // run events ordered
  puf.on(0x01, ev1);
  puf.on(0x02, ev2);
  puf.on(0x03, ev3);
  puf.on(0x04, ev4);
  puf.on(0x05, ev5);

  // run with error
  puf.on(0x06, err_ev1);
  puf.on(0x06, err_ev2);
  run();
}

void run() {
  RUN_TEST(test_puf_run_events_ordered);
  RUN_TEST(test_puf_stop_on_error);
}

}  // namespace puf_test
