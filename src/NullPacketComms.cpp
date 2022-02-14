/*
 *	Null Packet Comms Arduino Library
 *
 *	Copyright © 2022 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/Null-Packet-Comms-Arduino/>
 *
 *	A library for wrapping the arduino UART serial
 *	in a binary packet based communication protocol.
 *	See <https://wiki.nulltek.xyz/docs/protocols/npc/>
 */

#include "NullPacketComms.h"

NullPacketComms::NullPacketComms() {
  target_ = 0;
  len_ = 0;
  memset(payload_, 0, sizeof(payload_));
}

bool NullPacketComms::begin(uint32_t baud_rate) {
  switch (baud_rate) {
    case 115200:
    case 57600:
    case 38400:
    case 31250:
    case 28800:
    case 19200:
    case 14400:
    case 9600:
    case 4800:
    case 2400:
    case 1200:
    case 600:
    case 300:
      Serial.begin(baud_rate);
      return true;
    default:  // Unsupported / atypical baud-rate
      return false;
  }
}

void NullPacketComms::end() { Serial.end(); }

int NullPacketComms::available() { return Serial.available(); }

bool NullPacketComms::readPacket(bool manual_ack) {
  if (Serial.available() < 1) return false;  // No pending data.
  this->clean();                             // Clears last processed packet.
  uint8_t lrc = 0;     // For calculating LRC to check against the packet.
  uint8_t cursor = 0;  // For tracking the position in the packet.
  bool lrc_match = false;
  bool end_token = false;
  // Iterates while packet is being built and more data is coming in.
  while (Serial.available() > 0) {
    uint8_t inward = Serial.read() & 0xff;  // No byte case is a non-issue.
    if (cursor == 0) {                      // Start packet symbol.
      if (inward != '>') {                  // Packet not in sync.
        delay(50);  // Error case blindly allows buffer accumulation.
        continue;
      }
      cursor++;                // Valid byte added to the packet!
    } else if (cursor <= 2) {  // To, from, and length.
      lrc = (lrc + inward) & 0xff;
      if (cursor == 1) target_ = inward;
      cursor++;  // Valid byte added to the packet!
    } else if (cursor == 3) {
      len_ = inward;  // Set the pending packet length.
      lrc = (lrc + inward) & 0xff;
      cursor++;                      // Valid byte added to the packet!
    } else if (cursor < 4 + len_) {  // Payload.
      payload_[cursor - 4] = inward;
      lrc = (lrc + inward) & 0xff;
      cursor++;                       // Valid byte added to the packet!
    } else if (cursor == 4 + len_) {  // Checksum.
      lrc = ((lrc ^ 0xff) + 1) & 0xff;
      lrc_match = lrc == inward;
      cursor++;                       // Valid byte added to the packet!
    } else if (cursor == 5 + len_) {  // End packet symbol.
      if (inward == '<') end_token = true;
      break;
    }
    uint8_t local_gap = 0;  // Count the delay from the last byte
    while (Serial.available() < 1 && local_gap < 4) {
      // Can't have a byte interval > 100ms or something is wrong
      delay(25);
      local_gap++;
    }
  }
  if (cursor == 0) {
    writeAck(1, 2);  // Start symbol not found
    return false;    // Couldn't sync with a packet, don't ack
  }
  if (cursor < 5) {
    writeAck(1, 3);  // Malformed packet
    return false;
  }
  if (!lrc_match) {
    writeAck(target_, 4);  // Checksum mismatch.
    return false;
  }
  if (!end_token) {
    writeAck(target_, 5);  // End packet symbol not found.
    return false;
  }
  if (!manual_ack) {
    writeAck(target_, 0);  // Successful read, when auto-ack.
  }
  return true;
}

uint8_t NullPacketComms::writePacket(uint8_t target, uint8_t data[],
                                     uint8_t data_len) {
  if (data_len > 58) return 0;      // Packet can't exceed 64 bytes.
  uint8_t byte_count = 0;           // Record bytes sent in packet
  byte_count += Serial.write('>');  // Send start packet symbol
  uint8_t lrc = 0;                  // Compute LRC byte
  byte_count += Serial.write(0);    // Always communicating with host.
  byte_count += Serial.write(target);
  lrc = (lrc + target) & 0xff;
  byte_count += Serial.write(data_len);
  lrc = (lrc + data_len) & 0xff;
  for (uint8_t i = 0; i < data_len; i++) {  // Send the payload
    byte_count += Serial.write(data[i]);
    lrc = (lrc + data[i]) & 0xff;
  }
  lrc = ((lrc ^ 0xff) + 1) & 0xff;
  byte_count += Serial.write(lrc);  // Send the checksum
  byte_count += Serial.write('<');  // Send end packet symbol
  return byte_count;
}

bool NullPacketComms::writeAck(uint8_t target, uint8_t ack_code) {
  uint8_t data[1] = {ack_code};
  return writePacket(target, data, 1) == 7;  // ACK always 7 bytes
}

void NullPacketComms::clean() {
  len_ = 0;
  target_ = 0;
}
