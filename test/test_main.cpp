#include <Arduino.h>
#include <unity.h>

#include "test_state-machine.h"

void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);

  UNITY_BEGIN();
  state::init();
  UNITY_END();
}

void loop() {}
