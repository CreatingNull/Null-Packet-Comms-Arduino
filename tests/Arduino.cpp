/*
 *	Null Packet Comms Arduino Library Tests
 *
 *	Copyright © 2022 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/Null-Packet-Comms-Arduino/>
 *
 *	Mocked Arduino stub for testing the library.
 */

#include "Arduino.h"

HardwareSerial::HardwareSerial() { return; }

void HardwareSerial::begin(uint32_t baud) { return; }

void HardwareSerial::end() { return; }

uint8_t HardwareSerial::available() { return 0; }

uint8_t HardwareSerial::read() { return 0; }

uint8_t HardwareSerial::write(uint8_t data) { return 0; }

void HardwareSerial::flush() { return; }

HardwareSerial Serial = HardwareSerial();

void delay(int micros) { return; }
