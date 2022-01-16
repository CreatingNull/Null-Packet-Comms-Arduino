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

/*!
        Serial connection object to handled via NPC protocol.
*/
class NullPacketComms {
 public:
  NullPacketComms();
  uint8_t packet_tx[32];
  /*! Open a connection to the serial object.

        \param baud_rate Integer setting the standard Arduino UART baud rate to
     use.
  */
  bool init_port(uint32_t baud_rate, uint8_t buffer_size);
  bool read_packet();
  bool process_packet(uint8_t packet_len);
  uint8_t flush_rx_buffer();
  bool close_port();
  uint8_t packet_target_address;
  uint8_t packet_payload_len;
  uint8_t packet_payload[32];
  bool return_ack(uint8_t error_code, uint8_t remote_address,
                  uint8_t local_address);
  uint8_t generate_packet_data(const uint8_t payload[], uint8_t payload_len,
                               uint8_t remote_address, uint8_t local_address,
                               uint8_t packet_tx[]);
  bool send_packet(uint8_t packet_tx[], uint8_t packet_len);

 private:
  uint8_t packet[32];
};

#endif  // NULLPACKETCOMMS_H_
