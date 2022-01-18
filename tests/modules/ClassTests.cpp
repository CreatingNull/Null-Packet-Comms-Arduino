/*
 *	Null Packet Comms Arduino Library Tests
 *
 *	Copyright © 2022 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/Null-Packet-Comms-Arduino/>
 *
 *	Test Module for coverage of NullPacketComms class using mocked
 *  arduino.
 */

#include <gtest/gtest.h>

#include "../src/NullPacketComms/NullPacketComms.h"

namespace {

TEST(NPCObject, Constructor) {
  // Check the constructor for the object
  NullPacketComms testCom = NullPacketComms();
  // Sanity check the constructed state of the object
  ASSERT_EQ(testCom.target_, 0);
  ASSERT_EQ(testCom.len_, 0);
  ASSERT_EQ(sizeof(testCom.payload_), 58);  // 64 - 6
  // Check the payload array initialises all elements to 0
  for (int i = 0; i < sizeof(testCom.payload_); i++) {
    ASSERT_EQ(testCom.payload_[i], 0);
  }
}

TEST(NPCObject, Begin) {
  NullPacketComms testCom = NullPacketComms();
  // Check valid baud
  bool result = testCom.begin(57600);
  ASSERT_TRUE(result);
  // Check invalid baud
  result = testCom.begin(1);
  ASSERT_FALSE(result);
}

TEST(NPCObject, End) {
  NullPacketComms testCom = NullPacketComms();
  testCom.end();  // Just a stub for syntax
}

TEST(NPCObject, Available) {
  NullPacketComms testCom = NullPacketComms();
  uint8_t num_bytes = testCom.available();
  ASSERT_EQ(num_bytes, 0);  // Just a stub for syntax
}

}  // namespace
