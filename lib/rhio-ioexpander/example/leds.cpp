#include <Arduino.h>
#include <rhio-pinmap.h>

#include "rhio-ioexpander.h"

RhioIOExpander ioex;

void setup() {
  Serial.begin(9600);
  Serial.println("RhioIOExpander - Init test leds");
  delay(1000);

  // Initialize class
  ioex.begin();
  ioex.setupIOEXHalley();
}

void loop() {
  ioex.redLedOn();
  delay(1000);

  ioex.redLedOff();
  ioex.blueLedOn();
  delay(1000);

  ioex.blueLedOff();
  ioex.greenLedOn();
  delay(1000);

  ioex.turnLedsOff();
}
