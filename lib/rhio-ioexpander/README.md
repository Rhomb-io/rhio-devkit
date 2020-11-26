# FXL6408 library for Arduino

The FXL6408 library provides a an easy way to use the IO Expander FXL6408 controlled
with the I2C bus.

## Supported hardware

This library was developed using the arduino Framework and gives support to the Halley box,
a motherboard compatible with all the modules from Rhomb.io

## Example
 ### Blinking Leds
 ``` C++
#include <Arduino.h>
#include "Wire.h"

#define FXL6408_DEBUG Serial
#include "FXL6408.h"

FXL6408 ioex;

void setup() {
  Serial.begin(115200);
  // init the library
  ioex = FXL6408();
  ioex.setupIOEXHalley();
}

void loop() {
  // Enable RGB red on Halley
  ioex.redLedOn();
  ioex.greenLedOff();
  delay(1000);

  ioex.blueLedOn();
  ioex.redLedOff();
  delay(1000);

  ioex.greenLedOn();
  ioex.blueLedOff();
  delay(1000);

}
 ```

## Usage

First of all you must declare `FXL6408 ioex = FXL6408()` in order to give a local name
to the FXL6408 class and run the constructor of the class where functions `begin()` and
`setupIOEX()` takes place. This functions will set the default configuration of the
IO Expander. Also, the user has to make sure that the serial port is correctly configured.

To controll the IO Expander, the user has access to the following high logic functions:

+ `ioex::digitalRead(uint8_t port)`: This function reads the Input Status of the ports and returns
the state with `1` for HIGHSTATE or `0` for LOWSTATE.

+ `ioex::enableSPIMemory()`: This function its used to set the OUTPUT logic level to HIGHSTATE of
the PORT1. This will enable the CS port of the SPI Memory that mounts the Halley Box
allowing to the user to use it. If the memory is enabled, the function may print a message
using the serial port and return the value `1`.

+ `ioex::disableSPIMemory()`: This function its used to set the OUTPUT logic level to LOWSTATE of
the PORT1. This will disable the CS port of the SPI Memory that mounts the Halley Box
disabling the usage of it. If the memory is enabled, the function may print a message
using the serial port and return the value `0`.

+ `ioex::setUARTSlave2()`: This function its used to set the OUTPUT logic level to LOWSTATE of
the PORT2. This port is attached to the UART Switcher that mounts the halley box, and
when this function is called, the UART_B port of the master will be connected to the
UART Slave in the slot 2. If the Switcher is set on this configuration, the function
may print a message using the serial port and return the value `0`.

+ `ioex::setUARTSlaveCommon()`: This function its used to set the OUTPUT logic level to HIGHSTATE
of the PORT2. This port is attached to the UART Switcher that mounts the halley box, and
when this function is called, the UART_B port of the master will be connected to the
UART Common Port of both Slaves. If the Switcher is set on this configuration,
the function may print a message using the serial port and return the value `1`.


+ `ioex::redLedOn()`: This function will set the PORT3 to HIGHSTATE setting ON the Red led.

+ `ioex::redLedOff()`: This function will set the PORT3 to LOWSTATE setting OFF the Red led.

+ `ioex::greenLedOn()`: This function will set the PORT4 to HIGHSTATE setting ON the Green led.

+ `ioex::greenLedOff()`: This function will set the PORT4 to LOWSTATE setting OFF the Green led.

+ `ioex::blueLedOn()`: This function will set the PORT5 to HIGHSTATE setting ON the Blue led.

+ `ioex::blueLedOff()`: This function will set the PORT5 to LOWSTATE setting OFF the Blue led.

## License

This library was developed by Rhomb.io and has a GNU/GPL v3 license. For more information, check the License file.
