#include <Arduino.h>
#include <unity.h>

//#include "test_puf.h"
//#include "test_state-machine.h"

#include "test_flash.h"

void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);
  // pinMode(9, OUTPUT);

  UNITY_BEGIN();
  // state_test::init();
  // puf_test::init();
  flash_test::init();
  UNITY_END();
}

void loop() {}
