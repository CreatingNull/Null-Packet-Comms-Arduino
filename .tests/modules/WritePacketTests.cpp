/*
 *	Null Packet Comms Arduino Library Tests
 *
 *	Copyright © 2023 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/Null-Packet-Comms-Arduino/>
 *
 *	Test Module for coverage of NullPacketComms Writing functions
 *  using mocked arduino.
 */

#include <gtest/gtest.h>

#include "../src/NullPacketComms.h"

namespace {

TEST(NPCObject, WriteEmptyPacket) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  // Test an empty payload sends expected packet
  uint8_t data[]{};
  uint8_t limit[]{'>', 0, 1, 0, 255, '<'};

  uint8_t result = testCom.writePacket(1, data, 0);
  ASSERT_EQ(result, sizeof(limit));
  for (uint8_t i = 0; i < sizeof(limit); i++) {
    uint8_t sent_byte = Serial.pending_tx_.front();
    Serial.pending_tx_.pop();
    ASSERT_EQ(sent_byte, limit[i]);
  }
}

TEST(NPCObject, WriteTypicalPacket) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  // Test a typical packet
  uint8_t data[]{13, 0, 1, 12, 1, 0};
  uint8_t limit[]{'>',  0x00, 0x40, 0x06, 0x0d, 0x00,
                  0x01, 0x0c, 0x01, 0x00, 0x9f, '<'};

  uint8_t result = testCom.writePacket(64, data, sizeof(data));
  ASSERT_EQ(result, sizeof(limit));
  for (uint8_t i = 0; i < sizeof(limit); i++) {
    uint8_t sent_byte = Serial.pending_tx_.front();
    Serial.pending_tx_.pop();
    ASSERT_EQ(sent_byte, limit[i]);
  }
}

TEST(NPCObject, WriteMaxPacket) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  // Test a 64 byte packet.
  uint8_t data[58];
  memset(data, 1, sizeof(data));
  uint8_t limit[64];
  memset(limit, 1, sizeof(limit));
  limit[0] = '>';
  limit[1] = 0;
  limit[3] = sizeof(data);
  limit[sizeof(limit) - 1] = '<';
  limit[sizeof(limit) - 2] = 139;

  uint8_t result = testCom.writePacket(1, data, sizeof(data));
  ASSERT_EQ(result, sizeof(limit));
  for (uint8_t i = 0; i < sizeof(limit); i++) {
    uint8_t sent_byte = Serial.pending_tx_.front();
    Serial.pending_tx_.pop();
    ASSERT_EQ(sent_byte, limit[i]);
  }
}

TEST(NPCObject, WriteAck) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  // Check acknowledge packets are generated correctly
  uint8_t const limit[7]{'>', 0, 24, 1, 255, 232, '<'};
  bool result = testCom.writeAck(24, 255);
  ASSERT_TRUE(result);
  ASSERT_EQ(Serial.pending_tx_.size(), 7);
  for (uint8_t val : limit) {
    ASSERT_EQ(Serial.pending_tx_.front(), val);
    Serial.pending_tx_.pop();
  }
}

}  // namespace
