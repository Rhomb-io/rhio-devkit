#include <Arduino.h>
#include <unity.h>

// validate configuration
#if RHIO_TEST_ALL != 1 && RHIO_TEST_PUF != 1 && \
    RHIO_TEST_STATE_MACHINE != 1 && RHIO_TEST_FLASH != 1
#error \
    "Error, please enable at least one test module in platformio.ini (build_flags)"
#error "See more info about build_flags in readme.md (tests section)"
#endif

#if defined(RHIO_TEST_ALL) || defined(RHIO_TEST_PUF)
#include "test_puf.h"
#endif

#if defined(RHIO_TEST_ALL) || defined(RHIO_TEST_STATE_MACHINE)
#include "test_state-machine.h"
#endif

#if defined(RHIO_TEST_ALL) || defined(RHIO_TEST_FLASH)
#include "test_flash.h"
#endif

void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);
  // pinMode(9, OUTPUT);

  UNITY_BEGIN();

#if RHIO_TEST_ALL == 1 || RHIO_TEST_PUF == 1
  puf_test::init();
#endif

#if RHIO_TEST_ALL == 1 || RHIO_TEST_STATE_MACHINE == 1
  state_test::init();
#endif

#if RHIO_TEST_ALL == 1 || RHIO_TEST_FLASH == 1
  flash_test::init();
#endif

  UNITY_END();
}

void loop() {}
