# ![NullTek Documentation](resources/NullTekDocumentationLogo.png) Arduino Null Packet Comms

[![License](https://img.shields.io/:license-mit-blue.svg?style=flat-square)](LICENSE.md)

This is an arduino library that implements a binary packet-based communication protocol on top of the arduino Serial library.
This wrapper allows for robust generic data transfer between systems, it is heavily relied on for the [Arduino UOS](https://github.com/CreatingNull/UOS-Arduino) implementation.

For more information on this project and it's uses please see the [documentation](https://wiki.nulltek.xyz/protocols/npc/).

---

## Getting Started

This project is stand-alone and the only requirement is for it to be compiled used in arduino projects.
Packaged releases of the library can be obtained as zip files from the repository tags, the library can then be installed using the arduino library manager, see their [instructions](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries).

### Source Structure

The source code is written in C++ and contained within the `src/` subdir.
Most of the code is formatted to clang specifications, however this is automated via the [pre-commit](https://github.com/CreatingNull/UOS-Interface/actions/workflows/run-pre-commit.yml) framework, see repo [hooks](.pre-commit-config.yaml).

The pre-commit action is currently automated by GitHub actions CI, to verify against pushes and pull-requests.

## Donations

I just do this stuff for fun in my spare time, but feel free to:

[![Support via buymeacoffee](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/nulltek)

---

## License

The source of this repo uses the MIT open-source license, for details on the current licensing see LICENSE.md or click the badge above. 
*   Copyright 2022 © <a href="https://nulltek.xyz" target="_blank">NullTek</a>.
