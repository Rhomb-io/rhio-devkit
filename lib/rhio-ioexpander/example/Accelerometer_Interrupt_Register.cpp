#include <Arduino.h>

#include "FXL6408.h"
#include "rhio-LIS2HH12.h"

/***************************************************************
 * @author Pablo Mondéjar Sánchez and José Francisco Martí Martín
 *
 * This example uses the rhio-LIS2HH12 library to register
 * the movement of the board and sends an interruption that
 * would be registred on the PORT0 of IOExpander and
 * transmitted to the microcontroller.
 *
 * Download rhio-LIS2HH12 from:
 * https://gitlab.com/rhombio/rhio-libraries/rhio-LIS2HH12
 *
 ***************************************************************/

LIS2HH12 acel = LIS2HH12();
FXL6408 ioex;

void setup() {
  Serial.begin(115200);

  /***************************************************************
   * Set up IO Expander
   ***************************************************************/
  ioex.begin();
  ioex.setupIOEXHalley();  // using Hydra PCB

  /***************************************************************
   * Set up Accelerometer
   ***************************************************************/
  acel.begin();
  acel.setBasicConfig();

  /***************************************************************
   * Configure the interruption on each axis and
   * declare the output port on the IG1
   ***************************************************************/
  acel.setIntGenerator1(ENABLE_INT1, DISABLED_INT2);
  acel.setIntMode(0, IG1);
  acel.setMinDurationIG(30, IG1);
  acel.setXIE(2, IG1);
  acel.setYIE(8, IG1);
  acel.setZIE(32, IG1);
  acel.setThresholdIG1(40, 40, 160);  //* 160 = 1280 mg && 40 = 320 mg
}

void loop() {
  float x, y, z;
  acel.getAccelmG(&x, &y, &z);  //* Get the acceleration on 3 axis

  //* Show the accelerationon through the serial port *//

  Serial.print("x: ");
  Serial.println(x);

  Serial.print("y: ");
  Serial.println(y);

  Serial.print("z: ");
  Serial.println(z);

  //* Show the state of each port through the serial port *//

  uint8_t softInt = acel.getINT(IG1);
  Serial.print("Interrupt Software: ");
  Serial.println(softInt);

  uint8_t portStatus = ioex.digitalRead(PORT0);
  Serial.print("Input port state: ");
  Serial.println(portStatus);

  uint8_t interruptStatus = ioex.readInterrupt(PORT0);
  Serial.print("Interrupt Register: ");
  Serial.println(interruptStatus);

  if (interruptStatus == 1) {
    ioex.blueLedOn();
  }

  else {
    ioex.blueLedOff();
  }
  Serial.println("");
  Serial.println("");

  delay(1000);
}
