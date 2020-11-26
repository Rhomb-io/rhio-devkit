#include "rhio-ioexpander.h"

/**********************GENERAL**********************/

#if defined(FXL6408_DEBUG)
template <class T>
void ioex_debug(T str) {
  Serial.print("INFO: ");
  Serial.println(str);
}
#else
template <class T>
void ioex_debug(T str) {}
#endif

RhioIOExpander::RhioIOExpander() {}

bool RhioIOExpander::begin() {
  ioex_debug("Begin IOEX FXL6408");
  Wire.begin();
  Wire.setClock(100000);

  uint8_t init1 = readBit(RH_PORT5, RH_CONTROL);
  uint8_t init2 = readBit(RH_PORT6, RH_CONTROL);
  uint8_t init3 = readBit(RH_PORT7, RH_CONTROL);

  if (init1 == 1 && init2 == 0 && init3 == 1) {
    return 1;
  }

  return 0;
}

void RhioIOExpander::setupIOEXHalley() {
  ioex_debug("Setup IO Expander for Halley");

  //** Configuración de los puertos OUTPUT/INPUT **//

  Wire.beginTransmission(RH_IO_Address);
  Wire.write(RH_IOMODE);
  Wire.write(0x3E);
  Wire.endTransmission();

  //** Configuración de OUTPUTs a "0" **//

  Wire.beginTransmission(RH_IO_Address);
  Wire.write(RH_OUTPUTSTATE);
  Wire.write(0x00);
  Wire.endTransmission();

  //** Configuración de OUTPUT de alta impedancia desactivada **//

  Wire.beginTransmission(RH_IO_Address);
  Wire.write(RH_OUTPUTHIGHZ);
  Wire.write(0x00);
  Wire.endTransmission();

  //** Configuración de estado logico INPUT a "0" **//

  Wire.beginTransmission(RH_IO_Address);
  Wire.write(RH_LOGICINPUTSTATE);
  Wire.write(0x00);
  Wire.endTransmission();

  //** Configuración PU/PD desactivada **//

  Wire.beginTransmission(RH_IO_Address);
  Wire.write(RH_PULLENABLE);
  Wire.write(0x00);
  Wire.endTransmission();

  //** Configurar RH_PORT0 como generador de interrupciones **//

  Wire.beginTransmission(RH_IO_Address);
  Wire.write(RH_INTERRUPTION);
  Wire.write(0x254);
  Wire.endTransmission();
}

/**********************GENERAL**********************/

bool RhioIOExpander::digitalRead(uint8_t port) {
  bool bit = RhioIOExpander::readBit(port, RH_INPUTSTATE);

  return (bit == 1) ? true : false;
}

void RhioIOExpander::digitalWrite(uint8_t port, uint8_t state) {
  if (state == HIGH) {
    uint8_t val = ~port;
    RhioIOExpander::writeBit(val, port, RH_OUTPUTSTATE);
  }

  if (state == LOW) {
    RhioIOExpander::writeBit(0, port, RH_OUTPUTSTATE);
  }
}

bool RhioIOExpander::readInterrupt(uint8_t port) {
  bool bit = RhioIOExpander::readBit(port, RH_INTERRUPTIONSTATE);

  return (bit == 1) ? true : false;
}

void RhioIOExpander::setOutput(uint8_t port) {
  uint8_t val = ~port;
  RhioIOExpander::writeBit(val, port, RH_IOMODE);
}

void RhioIOExpander::setInput(uint8_t port) {
  RhioIOExpander::writeBit(0, port, RH_IOMODE);
}

void RhioIOExpander::setAllOutput() {
  RhioIOExpander::writeRegister(255, RH_IOMODE);
  ioex_debug("Set as output all ports");
}

void RhioIOExpander::setAllInput() {
  RhioIOExpander::writeRegister(0, RH_IOMODE);
  ioex_debug("Set as input all ports");
}

void RhioIOExpander::setOutputHighZ(uint8_t port) {
  uint8_t val = ~port;
  RhioIOExpander::writeBit(val, port, RH_OUTPUTHIGHZ);
  ioex_debug("Set High Z Output");
}

void RhioIOExpander::setOutputDefault(uint8_t port) {
  RhioIOExpander::writeBit(0, port, RH_OUTPUTHIGHZ);
  ioex_debug("Set default Output");
}

void RhioIOExpander::logicInputState(uint8_t port, uint8_t state) {
  if (state == HIGH) {
    uint8_t val = ~port;
    RhioIOExpander::writeBit(val, port, RH_OUTPUTSTATE);
    ioex_debug("Default input state set to HIGH");
  }

  if (state == LOW) {
    RhioIOExpander::writeBit(0, port, RH_OUTPUTSTATE);
    ioex_debug("Default input state set to LOW");
  }
}

void RhioIOExpander::setPullUpDown(uint8_t port, uint8_t mode) {
  uint8_t val = ~port;
  RhioIOExpander::writeBit(val, port, RH_PULLENABLE);
  if (mode == RH_PULLUP_IO) {
    RhioIOExpander::writeBit(val, port, RH_DEFINEPUPD);
    ioex_debug("Output type PullUp enabled");
  }
  if (mode == RH_PULLDOWN_IO) {
    RhioIOExpander::writeBit(0, port, RH_DEFINEPUPD);
    ioex_debug("Output type PullDown enabled");
  } else {
    ioex_debug("El modo definido es incorrecto");
  }
}

/**********************HALLEY**********************/

bool RhioIOExpander::disableSPIMemory() {
  char spimem = 0b00000010;
  bool bit = RhioIOExpander::readBit(RH_PORT1, RH_OUTPUTSTATE);

  if (bit == 1) {
    ioex_debug("SPI Memory already enabled");
    return 1;
  }

  RhioIOExpander::writeBit(spimem, RH_PORT1, 0x05);
  ioex_debug("SPI Memory Enabled");
  return 1;
}

bool RhioIOExpander::enableSPIMemory() {
  bool bit = RhioIOExpander::readBit(RH_PORT1, RH_OUTPUTSTATE);

  if (bit == 0) {
    ioex_debug("SPI Memory already disabled");
    return 0;
  }

  RhioIOExpander::writeBit(0, RH_PORT1, 0x05);
  ioex_debug("SPI Memory Disabled");
  return 0;
}

bool RhioIOExpander::setUARTSlave2() {
  bool bit = RhioIOExpander::readBit(RH_PORT2, RH_OUTPUTSTATE);

  if (bit == 0) {
    ioex_debug("UART slave 2 Ready");
    return 0;
  }

  RhioIOExpander::writeBit(0, RH_PORT2, RH_OUTPUTSTATE);
  ioex_debug("UART slave 2 Enabled");
  return 0;
}

bool RhioIOExpander::setUARTSlaveCommon() {
  bool bit = RhioIOExpander::readBit(RH_PORT2, RH_OUTPUTSTATE);

  if (bit == 1) {
    ioex_debug("UART slave common mode Ready");
    return 1;
  }

  RhioIOExpander::writeBit(0b00000100, RH_PORT2, RH_OUTPUTSTATE);
  ioex_debug("UART slave common mode Enabled");
  return 1;
}

void RhioIOExpander::redLedOn() {
  char ledr = 0b00001000;
  writeBit(ledr, RH_PORT3, 0x05);
}

void RhioIOExpander::redLedOff() { writeBit(0, RH_PORT3, 0x05); }

void RhioIOExpander::greenLedOn() {
  char ledg = 0b00010000;
  writeBit(ledg, RH_PORT4, 0x05);
}

void RhioIOExpander::greenLedOff() { writeBit(0, RH_PORT4, 0x05); }

void RhioIOExpander::blueLedOn() {
  char ledb = 0b00100000;
  writeBit(ledb, RH_PORT5, 0x05);
}

void RhioIOExpander::blueLedOff() { writeBit(0, RH_PORT5, 0x05); }

void RhioIOExpander::turnLedsOn() {
  char leds = 0b00111000;
  writeBit(leds, 0b11000111, 0x05);
}

void RhioIOExpander::turnLedsOff() { writeBit(0, 0b11000111, 0x05); }

/**********************UTILITY**********************/

uint8_t RhioIOExpander::readRegister(uint8_t regis) {
  uint8_t result = 0;

  Wire.beginTransmission(RH_IO_Address);
  Wire.write(regis);
  Wire.endTransmission();
  Wire.requestFrom(RH_IO_Address, 1);
  while (Wire.available()) {
    result = Wire.read();
  }
  return result;
}

void RhioIOExpander::writeRegister(uint8_t val, uint8_t regis) {
  Wire.beginTransmission(RH_IO_Address);
  Wire.write(regis);
  Wire.write(val);
  Wire.endTransmission();
}

bool RhioIOExpander::readBit(uint8_t port, uint8_t regis) {
  uint8_t direccion = 0;

  if (port == RH_PORT0) {
    direccion = 0;
  }
  if (port == RH_PORT1) {
    direccion = 1;
  }
  if (port == RH_PORT2) {
    direccion = 2;
  }
  if (port == RH_PORT3) {
    direccion = 3;
  }
  if (port == RH_PORT4) {
    direccion = 4;
  }
  if (port == RH_PORT5) {
    direccion = 5;
  }
  if (port == RH_PORT6) {
    direccion = 6;
  }
  if (port == RH_PORT7) {
    direccion = 7;
  }

  uint8_t read = readRegister(regis);
  uint8_t bit = read >> direccion;
  bit = bit & 1;
  return bit;
}

void RhioIOExpander::writeBit(uint8_t val, uint8_t port, uint8_t regis) {
  uint8_t read, result, val2;
  read = readRegister(regis);

  result = read & port;
  val2 = result | val;

  Wire.beginTransmission(RH_IO_Address);
  Wire.write(regis);
  Wire.write(val2);
  Wire.endTransmission();
}
