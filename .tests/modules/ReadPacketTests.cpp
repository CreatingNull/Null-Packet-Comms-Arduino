/*
 *	Null Packet Comms Arduino Library Tests
 *
 *	Copyright © 2023 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/Null-Packet-Comms-Arduino/>
 *
 *	Test Module for coverage of NullPacketComms Reading functions
 *  using mocked arduino.
 */

#include <gtest/gtest.h>

#include <chrono>  // NOLINT [build/c++11]

#include "../src/NullPacketComms.h"

namespace {

TEST(NPCObject, ReadPacketNoData) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  // Check returns false if no pending data
  bool result = testCom.readPacket();
  ASSERT_FALSE(result);
}

TEST(NPCObject, ReadPacketInvalidData) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  // Add some dummy data to ensure the clean works correctly.
  testCom.len_ = 1;
  testCom.target_ = 255;
  Serial.pending_rx_.push(0);  // Invalid packet data
  bool result = testCom.readPacket();
  ASSERT_FALSE(result);        // Check fails
  ASSERT_EQ(testCom.len_, 0);  // Check object is cleaned correctly.
  ASSERT_EQ(testCom.target_, 0);
}

TEST(NPCObject, ReadTypicalPacket) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  uint8_t const data[]{'>',  0x02, 0x40, 0x06, 0x0d, 0x00,
                       0x01, 0x0c, 0x01, 0x00, 0x9d, '<'};
  uint8_t limit_payload[]{13, 0, 1, 12, 1, 0};
  uint8_t limit_target = 2;
  for (uint8_t val : data) Serial.pending_rx_.push(val);

  // Check manual ACK first
  bool result = testCom.readPacket(true);
  ASSERT_TRUE(result);
  ASSERT_TRUE(Serial.pending_rx_.empty());  // Bytes consumed
  ASSERT_TRUE(Serial.pending_tx_.empty());  // No ACK

  // Check automatic ACK API
  Serial = HardwareSerial();  // Reconstruct
  for (uint8_t val : data) Serial.pending_rx_.push(val);
  result = testCom.readPacket();
  ASSERT_TRUE(result);
  ASSERT_TRUE(Serial.pending_rx_.empty());
  // Check object populates correctly
  ASSERT_EQ(testCom.target_, limit_target);
  ASSERT_EQ(testCom.len_, sizeof(limit_payload));
  for (uint8_t i = 0; i < sizeof(limit_payload); i++)
    ASSERT_EQ(testCom.payload_[i], limit_payload[i]);
  // Ensure ACK staged.
  ASSERT_EQ(Serial.pending_tx_.size(), 7);
  for (uint8_t i = 0; i < 5; i++) {
    if (i == 2)  // Check ACK addressed correctly
      ASSERT_EQ(Serial.pending_tx_.front(), data[1]);
    else if (i == 4)  // Check payload indicates ack
      ASSERT_EQ(Serial.pending_tx_.front(), 0);
    Serial.pending_tx_.pop();
  }
}

TEST(NPCObject, ReadPacketTimeout) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct
  // Check read times out after 500ms
  // Use a partial packet
  uint8_t const data[]{'>', 0x02, 0x40, 0x06, 0x0d, 0x00};
  for (uint8_t val : data) Serial.pending_rx_.push(val);
  auto start_time = std::chrono::high_resolution_clock::now();
  testCom.readPacket();
  auto end_time = std::chrono::high_resolution_clock::now();
  int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                    end_time - start_time)
                    .count();
  // Should timeout after at least 100ms and at most 125ms.
  ASSERT_GE(elapsed, 100);
  ASSERT_LT(elapsed, 120);
}

TEST(NPCObject, ReadMaxPacket) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  // Test a 64 byte packet.
  uint8_t limit[58];
  memset(limit, 1, sizeof(limit));
  uint8_t data[64];
  memset(data, 1, sizeof(data));
  data[0] = '>';
  data[1] = 0;
  data[3] = sizeof(limit);
  data[sizeof(data) - 1] = '<';
  data[sizeof(data) - 2] = 139;

  for (uint8_t val : data) Serial.pending_rx_.push(val);

  bool result = testCom.readPacket(true);
  ASSERT_TRUE(result);

  for (uint8_t i = 0; i < sizeof(limit); i++)
    ASSERT_EQ(testCom.payload_[i], limit[i]);
}

TEST(NPCObject, ReadEmptyPacket) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  // Check can read a packet with no payload
  uint8_t const data[]{'>', 0, 1, 0, 255, '<'};
  for (uint8_t val : data) Serial.pending_rx_.push(val);

  bool result = testCom.readPacket(true);
  ASSERT_TRUE(result);
  ASSERT_EQ(testCom.len_, 0);
}

TEST(NPCObject, ReadNoStartSymbol) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();           // Reconstruct
  uint8_t const data[]{0, 1, 0, 255};  // Too short
  for (uint8_t val : data) Serial.pending_rx_.push(val);
  bool result = testCom.readPacket();
  ASSERT_FALSE(result);
  ASSERT_EQ(Serial.pending_tx_.size(), 7);
  for (uint8_t i = 0; i < 5; i++) {
    if (i == 2)  // Verify addressing, always 1.
      ASSERT_EQ(Serial.pending_tx_.front(), 1);
    else if (i == 4)  // Check NACK error code
      ASSERT_EQ(Serial.pending_tx_.front(), 2);
    Serial.pending_tx_.pop();
  }
}

TEST(NPCObject, ReadMalformed) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  // Check NACK case triggers correctly.
  uint8_t const data[]{'>', 0, 1, 0};  // Too short
  for (uint8_t val : data) Serial.pending_rx_.push(val);
  bool result = testCom.readPacket();
  ASSERT_FALSE(result);
  ASSERT_EQ(Serial.pending_tx_.size(), 7);
  for (uint8_t i = 0; i < 5; i++) {
    if (i == 2)  // Verify addressing, always 1.
      ASSERT_EQ(Serial.pending_tx_.front(), 1);
    else if (i == 4)  // Check NACK error code
      ASSERT_EQ(Serial.pending_tx_.front(), 3);
    Serial.pending_tx_.pop();
  }
}

TEST(NPCObject, ReadLrcMismatch) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  // Check NACK case triggers correctly.
  uint8_t const data[]{'>',  0x02, 0x40, 0x06, 0x0d, 0x00,
                       0x01, 0x0c, 0x01, 0x00, 0x9f, '<'};
  for (uint8_t val : data) Serial.pending_rx_.push(val);
  bool result = testCom.readPacket();
  ASSERT_FALSE(result);
  ASSERT_EQ(Serial.pending_tx_.size(), 7);
  for (uint8_t i = 0; i < 5; i++) {
    if (i == 2)  // Verify addressing.
      ASSERT_EQ(Serial.pending_tx_.front(), 2);
    else if (i == 4)  // Check NACK error code
      ASSERT_EQ(Serial.pending_tx_.front(), 4);
    Serial.pending_tx_.pop();
  }
}

TEST(NPCObject, ReadNoEndSymbol) {
  NullPacketComms testCom = NullPacketComms();
  Serial = HardwareSerial();  // Reconstruct

  // Check NACK case triggers correctly.
  uint8_t const data[]{'>',  0x02, 0x40, 0x06, 0x0d, 0x00,
                       0x01, 0x0c, 0x01, 0x00, 0x9d};
  for (uint8_t val : data) Serial.pending_rx_.push(val);
  bool result = testCom.readPacket();
  ASSERT_FALSE(result);
  ASSERT_EQ(Serial.pending_tx_.size(), 7);
  for (uint8_t i = 0; i < 5; i++) {
    if (i == 2)  // Verify addressing.
      ASSERT_EQ(Serial.pending_tx_.front(), 2);
    else if (i == 4)  // Check NACK error code
      ASSERT_EQ(Serial.pending_tx_.front(), 5);
    Serial.pending_tx_.pop();
  }
}

}  // namespace
