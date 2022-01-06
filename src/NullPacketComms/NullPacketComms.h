/*
 *	Null Packet Comms Arduino Library
 *
 *	Copyright © 2022 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/Null-Packet-Comms-Arduino/>
 *
 *	A library for wrapping the arduino UART serial
 *	in a binary packet based communication protocol.
 *	See <https://wiki.nulltek.xyz/protocols/npc/>
 */

#ifndef NULLPACKETCOMMS_H_
#define NULLPACKETCOMMS_H_

#include <Arduino.h>

class NullPacketComms {
 public:
  NullPacketComms();
  byte packet_tx[32];
  bool init_port(uint32_t baud_rate, uint8_t buffer_size);
  bool read_packet();
  bool process_packet(uint8_t packet_len);
  uint8_t flush_rx_buffer();
  bool close_port();
  uint8_t packet_target_address;
  uint8_t packet_payload_len;
  byte packet_payload[32];
  bool return_ack(uint8_t error_code, uint8_t remote_address,
                  uint8_t local_address);
  uint8_t generate_packet_data(const byte payload[], uint8_t payload_len,
                               uint8_t remote_address, uint8_t local_address,
                               byte packet_tx[]);
  bool send_packet(byte packet_tx[], uint8_t packet_len);

 private:
  byte packet[32];
};

#endif  // NULLPACKETCOMMS_H_
