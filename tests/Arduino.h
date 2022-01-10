/*
 *	Null Packet Comms Arduino Library Tests
 *
 *	Copyright © 2022 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/Null-Packet-Comms-Arduino/>
 *
 *	Mocked Arduino stub for testing the library.
 */
#ifndef TESTS_ARDUINO_H_
#define TESTS_ARDUINO_H_

#include <stdio.h>
#include <stdlib.h>

#define uint8_t u_int8_t
#define uint16_t u_int16_t
#define uint32_t u_int32_t

class HardwareSerial {
 public:
  HardwareSerial();
  void begin(uint32_t baud);
  void end();
  uint8_t available();
  uint8_t read();
  uint8_t write(uint8_t data);
  void flush();
};

extern HardwareSerial Serial;

void delay(int micros);

#endif  // TESTS_ARDUINO_H_
