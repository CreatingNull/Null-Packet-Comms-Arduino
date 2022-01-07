# ![NullTek Documentation](resources/NullTekDocumentationLogo.png) Arduino Null Packet Comms

[![License](https://img.shields.io/:license-mit-blue.svg?style=flat-square)](LICENSE.md)
[![Codacy grade](https://img.shields.io/codacy/grade/ec4a482e4a4f4fbdb0ddb0a268916f23?logo=codacy&style=flat-square)](https://app.codacy.com/gh/CreatingNull/Null-Packet-Comms-Arduino/dashboard?branch=master)
[![Pre-commit](https://img.shields.io/github/workflow/status/CreatingNull/Null-Packet-Comms-Arduino/pre-commit?logo=pre-commit&style=flat-square&label=code%20format)](https://github.com/CreatingNull/Null-Packet-Comms-Arduino/actions/workflows/run-pre-commit.yaml)
[![Build](https://img.shields.io/github/workflow/status/CreatingNull/Null-Packet-Comms-Arduino/build?logo=github&style=flat-square&label=build)](https://github.com/CreatingNull/Null-Packet-Comms-Arduino/actions/workflows/run-build.yaml)

This is an arduino library that implements a binary packet-based communication protocol on top of the arduino Serial library.
This wrapper allows for robust generic data transfer between systems, it is heavily relied on for the [Arduino UOS](https://github.com/CreatingNull/UOS-Arduino) implementation.

For more information on this project and its uses please see the [documentation](https://wiki.nulltek.xyz/protocols/npc/).

---

## Getting Started

This project is stand-alone and the only requirement is for it to be used in arduino projects.
Packaged releases of the library can be obtained as zip files from the repository tags, the library can then be installed using the arduino library manager, see their [instructions](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries).

### Source Structure

The source code is written in C++ and contained within the `src/` subdir.
Most of the code is formatted to clang specifications, however this is automated via the [pre-commit](https://github.com/pre-commit/pre-commit) framework, see repo [hooks](.pre-commit-config.yaml).
The hook's `LLVM` and `cppcheck` dependencies should be installed for the OS, as well as those defined in [development-requirements](resources/development-requirements.txt) to correctly execute the pre-commit tasks.

The pre-commit action is currently automated by GitHub actions CI, to verify against pushes and pull-requests.

## Donations

I just do this stuff for fun in my spare time, but feel free to:

[![Support via buymeacoffee](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/nulltek)

---

## License

The source of this repo uses the MIT open-source license, for details on the current licensing see [LICENSE](LICENSE.md) or click the badge above.
