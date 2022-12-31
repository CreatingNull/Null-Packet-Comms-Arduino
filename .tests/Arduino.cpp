/*
 *	Null Packet Comms Arduino Library Tests
 *
 *	Copyright © 2023 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/Null-Packet-Comms-Arduino/>
 *
 *	Mocked Arduino stub for testing the library.
 */

#include "Arduino.h"
// The following is for importing the sleep function cross platform.
#include <chrono>  // NOLINT [build/c++11]
#include <thread>  // NOLINT [build/c++11]

HardwareSerial::HardwareSerial() : pending_rx_(), pending_tx_() {}

void HardwareSerial::begin(uint32_t baud) { return; }

void HardwareSerial::end() { return; }

uint8_t HardwareSerial::available() { return pending_rx_.size(); }

uint8_t HardwareSerial::read() {
  if (available() > 0) {
    uint8_t data = pending_rx_.front();
    pending_rx_.pop();
    return data;
  }
  return 0;
}

uint8_t HardwareSerial::write(uint8_t data) {
  pending_tx_.push(data);
  return 1;
}

void HardwareSerial::flush() { return; }

HardwareSerial Serial = HardwareSerial();

void delay(int millis) {
  std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}
