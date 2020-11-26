#pragma once

#include "Arduino.h"
#include "Wire.h"

/**
 * @brief Definition of I2C adress
 */
#define RH_IO_Address 0x43

#define RH_PULLUP_IO 1
#define RH_PULLDOWN_IO 0

/**
 * @brief Definition of all the registers available
 */
#define RH_CONTROL 0x01
#define RH_IOMODE 0x03
#define RH_OUTPUTSTATE 0x05
#define RH_OUTPUTHIGHZ 0x07
#define RH_LOGICINPUTSTATE 0x09
#define RH_PULLENABLE 0x0B
#define RH_DEFINEPUPD 0x0D
#define RH_INPUTSTATE 0x0F
#define RH_INTERRUPTION 0x11
#define RH_INTERRUPTIONSTATE 0x13

/**
 * @brief Definition of all the ports available
 */
#define RH_PORT0 0b11111110
#define RH_PORT1 0b11111101
#define RH_PORT2 0b11111011
#define RH_PORT3 0b11110111
#define RH_PORT4 0b11101111
#define RH_PORT5 0b11011111
#define RH_PORT6 0b10111111
#define RH_PORT7 0b01111111

class RhioIOExpander {
 public:
  RhioIOExpander();

  /**
   * @fn bool begin()
   *
   *  @brief initializes the I2C bus and execute @fn void setupIOEX()
   *  which configures the presets of the IO Expander
   *
   *  @return if the control register of the IO Expander is correctly
   *  configured the value returned will be 1, otherwise will be 0
   */
  bool begin();

  /**
   * @fn bool digitalRead(uint8_t port)
   *
   *  @brief reads the Input state of the port selectd
   *
   *  @param port needs to be the Port defined in the macros
   *
   *  @return return 1 when the port is on HIGH state
   *  return 0 when the port is on LOW state
   */
  bool digitalRead(uint8_t port);
  void digitalWrite(uint8_t port, uint8_t state);

  void setOutput(uint8_t port);
  void setAllOutput();
  void setInput(uint8_t port);
  void setAllInput();

  void setOutputHighZ(uint8_t port);
  void setOutputDefault(uint8_t port);

  void logicInputState(uint8_t port, uint8_t state);
  void setPullUpDown(uint8_t port, uint8_t mode);

  // ---------------------------------------------------------

  /**
   * @fn void setupIOEXHalley()
   *
   *  @brief configures all ports with the hardware presets of the Halley
   */
  void setupIOEXHalley();

  /**
   * @fn bool enableSPIMemory()
   *
   *  @brief enable the SPI memory
   *
   *  @return return 1 when the SPI Memory is enabled
   */
  bool enableSPIMemory();

  /**
   * @fn bool disableSPIMemory()
   *
   *  @brief disable the SPI memory. This is the default
   *  configuration of this port.
   *
   *  @return return 0 when the SPI Memory is disabled
   */
  bool disableSPIMemory();

  /**
   * @fn bool setUARTSlave2()
   *
   *  @brief the UART-B port of the master will be attached
   *  to the UART port of the slave 2. This is the default
   *  configuration of this port
   *
   *  @return return 0 when the UART Slave 2 is enabled
   */
  bool setUARTSlave2();

  /**
   * @fn bool setUARTSlaveCommon()
   *
   *  @brief the UART-B port of the master will be attached
   *  to the UART common port of the Slaves
   *
   *  @return return 1 when the common UART ports of the
   *  Slave are enabled
   */
  bool setUARTSlaveCommon();

  /**
   * @fn void redLedOn()
   *
   *  @brief set the Red Led port to HIGHSTATE
   */
  void redLedOn();

  /**
   * @fn void redLedOff()
   *
   *  @brief set the Red Led port to LOWSTATE
   */
  void redLedOff();

  /**
   * @fn void greenLedOn()
   *
   *  @brief set the Green Led port to HIGHSTATE
   */
  void greenLedOn();

  /**
   * @fn void greenLedOff()
   *
   *  @brief set the Green Led port to LOWSTATE
   */
  void greenLedOff();

  /**
   * @fn void blueLedOn()
   *
   *  @brief set the Blue Led port to HIGHSTATE
   */
  void blueLedOn();

  /**
   * @fn void blueLedOff()
   *
   *  @brief set the Blue Led port to LOWSTATE
   */
  void blueLedOff();

  /**
   * @fn void turnLedsOn()
   *
   *  @brief set the all the Leds ports to HIGHSTATE
   */
  void turnLedsOn();

  /**
   * @fn void turnLedsOff()
   *
   *  @brief set the all the Leds ports to LOWSTATE
   */
  void turnLedsOff();

  /**
   * @fn bool readInterrupt(uint8_t port)
   *
   *  @brief reads the port
   *
   *  @param port needs to be the Port defined in the macros
   *
   *  @return the state of the port, 1 for an interruption detected
   *  0 for normal mode
   */
  bool readInterrupt(uint8_t port);

 private:
  /**
   * @fn uint8_t readRegister(uint8_t regis)
   *
   *  @brief reads the register status
   *
   *  @param must be a register defined on the macros
   *
   *  @return byte written on the register
   */
  uint8_t readRegister(uint8_t regis);

  /**
   * @fn void writeRegister(uint8_t val, uint8_t regis)
   *
   *  @brief writes the status byte defined on the register
   *
   *  @param byte to be written on the register
   *
   *  @param must be a register defined on the macros
   */
  void writeRegister(uint8_t val, uint8_t regis);

  /**
   * @fn bool readBit(uint8_t regis, uint8_t port)
   *
   *  @brief reads one bit of the register
   *
   *  @param must be a port defined on the macros
   *
   *  @param must be a register defined on the macros
   *
   *  @return bit selected written on the register
   */
  bool readBit(uint8_t regis, uint8_t port);

  /**
   * @fn void writeBit(uint8_t val, uint8_t port, uint8_t regis)
   *
   *  @brief writes one bit on the register
   *
   *  @param must be a mask for the bit selected with the value the user wants
   * to set e.g. to set the PORT3 to "1" -> val = 0b0000 1000 e.g. to set the
   * PORT3 to "0" -> val = 0b0000 0000
   *
   *  @param must be a port defined on the macros
   *
   *  @param must be a register defined on the macros
   */
  void writeBit(uint8_t val, uint8_t port, uint8_t regis);
};
