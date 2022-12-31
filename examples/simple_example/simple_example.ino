/*
 *	Null Packet Comms Arduino Library
 *
 *	Copyright © 2023 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/Null-Packet-Comms-Arduino/>
 *
 *	Example sketch which reads addition (address 10) and
 *  subtraction (address 11) actions with a numeric payload,
 *  these packets are then summed on an accumulator and returned
 *  with a read (address 12) command.
 */

// Include the NPC arduino library
#include "NullPacketComms.h"

// Create a global com wrapper
NullPacketComms com = NullPacketComms();
int accumulator = 0;

void setup() {
  // 0 our accumulator
  // Open the UART connection
  com.begin(9600);
  // To use the UART for other purposes during execution.
  // You may chose to begin in the loop
  // and end when appropriate.
}

void loop() {
  // Check if there is data pending
  if (com.available() > 0) {
    // Read the pending packet.
    // Check pending packet is valid.
    if (com.readPacket()) {                    // reads and automatically acks
      if (com.target_ == 10 && com.len_ == 1)  // addition
        accumulator += com.payload_[0];
      if (com.target_ == 11 && com.len_ == 1)  // subtraction
        accumulator -= com.payload_[0];
      if (com.target_ == 12) {  // return accumulator
        // Split accumulator into its bytes to return as little endian
        uint8_t payload[2] = {highByte(accumulator), lowByte(accumulator)};
        // Respond with the current value to the query packet address
        com.writePacket(com.target_, payload, sizeof(payload));
      }
    }
  }
}
