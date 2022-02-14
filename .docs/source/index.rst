.. NPC Arduino documentation master file.

Null Packet Comms Arduino
=========================

This is an arduino library that implements a binary packet-based communication protocol on top of the arduino Serial library.
This wrapper allows for robust generic data transfer between systems, it is heavily relied on for the `Arduino UOS <https://github.com/CreatingNull/UOS-Arduino>`_ implementation.

The library exposes a class which is designed to mimic the Serial API, but using formatted packets.

.. toctree::
   :maxdepth: 2
   :caption: Documentation:

   api
   changes
