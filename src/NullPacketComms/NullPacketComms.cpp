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

#include "NullPacketComms.h"

NullPacketComms::NullPacketComms() {
  packet_target_address = 0;
  packet_payload_len = 0;
  packet_tx = memset(packet_tx, 0, sizeof(packet_tx));
  packet_payload = memset(packet_payload, 0, sizeof(packet_payload));
  packet = memset(packet, 0, sizeof(packet));
}

bool NullPacketComms::init_port(uint32_t baud_rate, uint8_t buffer_size) {
  packet_payload[buffer_size - 6];
  packet[buffer_size];
  packet_tx[buffer_size];
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

bool NullPacketComms::close_port() {
  Serial.end();
  return true;
}

bool NullPacketComms::read_packet() {
  int packet_length = 0;
  int read_delay = 10;
  uint8_t LRC = 0;
  bool complete = false;
  bool checksum_match = false;
  while (Serial.available() > 0) {
    int incoming = Serial.read();
    if (incoming < 0) {
      continue;  // Bad read or data not actually available.
    }
    if (packet_length == 0) {  // header
      if (incoming == '>') {
        packet[packet_length] = incoming;
        LRC = 0;
        packet_length++;
      }
    } else if (packet_length >= 1 &&
               packet_length <= 3) {  // to address, from address length
      packet[packet_length] = incoming;
      LRC = (LRC + incoming) & 0xff;
      packet_length++;
    } else if (packet_length >= 4 &&
               packet_length <= 3 + packet[3]) {  // payload
      packet[packet_length] = incoming;
      LRC = (LRC + incoming) & 0xff;
      packet_length++;
    } else if (packet_length == 4 + packet[3]) {  // checksum
      packet[packet_length] = incoming;
      packet_length++;
      LRC = ((LRC ^ 0xff) + 1) & 0xff;
      if (LRC == packet[packet_length - 1]) {
        checksum_match = true;
      }
    } else if (packet_length = 5 + packet[3]) {  // footer
      if (incoming == '<') {
        packet[packet_length] = incoming;
        packet_length++;
        complete = true;
      }
    }
    if (!complete &&
        Serial.available() ==
            0) {  // if the next byte hasn't arrived yet, delay based on baud
      for (int i = 0; i < read_delay; i++) {
        if (Serial.available() > 0) {
          break;
        }
        delay(1);
      }
    }
  }
  if (complete && checksum_match) {
    process_packet(packet_length);
  }
  return complete && checksum_match;
}

uint8_t NullPacketComms::flush_rx_buffer() {
  uint8_t c = 0;
  while (Serial.read() >= 0) {  // Consume waiting bytes
    c++;
  }
  return c;
}

bool NullPacketComms::process_packet(uint8_t packet_len) {
  packet_target_address = packet[1];
  packet_payload_len = packet[3];
  for (int i = 0; i < packet_payload_len; i++) {
    packet_payload[i] = packet[i + 4];
  }
  return true;
}

uint8_t NullPacketComms::generate_packet_data(const uint8_t payload[],
                                              uint8_t payload_len,
                                              uint8_t remote_address,
                                              uint8_t local_address,
                                              uint8_t packet_tx[]) {
  uint8_t byte_count = 0;
  uint8_t LRC = 0;
  packet_tx[byte_count] = '>';
  byte_count++;  // start packet
  packet_tx[byte_count] = remote_address;
  LRC = (LRC + packet_tx[byte_count]) & 0xff;
  byte_count++;  // to address
  packet_tx[byte_count] = local_address;
  LRC = (LRC + packet_tx[byte_count]) & 0xff;
  byte_count++;  // from address
  packet_tx[byte_count] = payload_len;
  LRC = (LRC + packet_tx[byte_count]) & 0xff;
  byte_count++;  // data length
  // populate payload
  for (int i = 0; i < payload_len; i++) {
    packet_tx[byte_count] = payload[i];
    LRC = (LRC + packet_tx[byte_count]) & 0xff;
    byte_count++;
  }
  LRC = ((LRC ^ 0xff) + 1) & 0xff;
  packet_tx[byte_count] = LRC;
  byte_count++;  // longitudinal redundancy checksum
  packet_tx[byte_count] = '<';
  byte_count++;  // end packet
  return byte_count;
}

bool NullPacketComms::return_ack(uint8_t error_code, uint8_t remote_address,
                                 uint8_t local_address) {
  uint8_t data[1] = {error_code};
  uint8_t byte_len =
      generate_packet_data(data, 1, remote_address, local_address, packet_tx);
  return send_packet(packet_tx, byte_len);
}

bool NullPacketComms::send_packet(uint8_t packet_tx[], uint8_t packet_len) {
  uint8_t count_bytes = 0;
  for (int i = 0; i < packet_len; i++) {
    count_bytes += Serial.write(packet_tx[i]);
  }
  Serial.flush();
  if (count_bytes != packet_len - 1) {
    return false;
  }
  return true;
}
