/*
 *	Null Packet Comms Arduino Library Tests
 *
 *	Copyright © 2022 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/Null-Packet-Comms-Arduino/>
 *
 *	Test Module for coverage of NullPacketComms functions using mocked
 *arduino.
 */

#include <gtest/gtest.h>

#include "NullPacketComms.h"

namespace {

TEST(NPCHelperFunctions, Static) {
  NullPacketComms testCom = NullPacketComms();
  uint8_t gen_packet[32];
  uint8_t payload[1] = {1};
  uint8_t packet_length =
      testCom.generate_packet_data(payload, 1, 0, 1, gen_packet);
  // Verify a full length packet is built
  EXPECT_EQ(packet_length, 7);
  // Verify the data in the packet is correct
  const uint8_t packet_limit[7] = {62, 0, 1, 1, 1, 0xfd, 60};
  for (int i = 0; i < packet_length; i++) {
    EXPECT_EQ(gen_packet[i], packet_limit[i]);
  }
}

}  // namespace
