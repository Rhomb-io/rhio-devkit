#ifndef UNITTEST_TRANSPORT_H
#define UNITTEST_TRANSPORT_H

#include <Arduino.h>
#include <stdio.h>

#if defined(ARDUINO_SAMD_ZERO)
#define RH_TEST_DEBUG SerialUSB
#else
#define RH_TEST_DEBUG Serial
#endif

void unittest_uart_begin() {
  RH_TEST_DEBUG.begin(9600);

#if defined(ARDUINO_SAMD_ZERO)
  while (!RH_TEST_DEBUG)
    ;
#endif
}

void unittest_uart_putchar(char c) { RH_TEST_DEBUG.write(c); }

void unittest_uart_flush() { RH_TEST_DEBUG.flush(); }

void unittest_uart_end() {}

#endif
