#include <Arduino.h>
#include <unity.h>

#if defined(RHIO_TEST_ALL) || defined(RHIO_TEST_PUF)
#include "test_puf.h"
#endif

#if defined(RHIO_TEST_ALL) || defined(RHIO_TEST_STATE_MACHINE)
#include "test_state-machine.h"
#endif

void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);
  pinMode(9, OUTPUT);

  UNITY_BEGIN();

#if defined(RHIO_TEST_ALL) || defined(RHIO_TEST_PUF)
  puf_test::init();
#endif

#if defined(RHIO_TEST_ALL) || defined(RHIO_TEST_STATE_MACHINE)
  state_test::init();
#endif

  UNITY_END();
}

void loop() {}
