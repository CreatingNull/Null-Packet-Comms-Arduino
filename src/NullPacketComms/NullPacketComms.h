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
  /*! Constructor to initialise the wrapper. */
  NullPacketComms();

  //! Stores the to address of the last rx packet.
  uint8_t target_;
  //! Stores the payload length populated with the last rx packet.
  uint8_t len_;
  //! Stores the payload from the last rx packet.
  uint8_t payload_[58];

  /*! Opens the connection to the UART port.

        \param baud_rate Standard UART baud rate to use.
        \return `true` if opened `false` if unsupported baud.
  */
  bool begin(uint32_t baud_rate);

  /*! Closes the connection to the UART port. */
  void end();

  /*! Number bytes waiting in the serial buffer.

     \return number of bytes.
  */
  int available();

  /*! Reads the next packet from the serial buffer.

     \param manual_ack (optional) Set `true` to respond ACK
                in client code.
     \return `true` if read success, `false` otherwise.
  */
  bool readPacket(bool manual_ack = false);

  /*! Builds a data packet and sends it to the host system

        \param target Of the system to respond to.
        \param data Payload array to populate into the packet.
                \param data_len Length of the payload array.
        \return Number of bytes successfully sent.
  */
  uint8_t writePacket(uint8_t target, uint8_t data[], uint8_t data_len);

  /*! Sends an ack packet in response to a resolved rx packet

        \param target address of system we are responding from.
        \param ack_code NACK error code or `0` for ACK.
        \return `true` if ack was sent successfully else `false`.
  */
  bool writeAck(uint8_t target, uint8_t ack_code);

 private:
  /*! Clears the state of the RX fields. */
  void clean();
};

#endif  // NULLPACKETCOMMS_H_
