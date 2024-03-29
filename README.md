# ![NullTek Documentation](https://raw.githubusercontent.com/CreatingNull/NullTek-Assets/main/img/logo/NullTekDocumentationLogo.png)Arduino Null Packet Comms

[![License](https://img.shields.io/:license-mit-blue.svg?style=flat-square)](https://github.com/CreatingNull/Null-Packet-Comms-Arduino/blob/master/LICENSE.md)
[![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/creatingnull/null-packet-comms-arduino?style=flat-square&color=orange)](https://github.com/CreatingNull/Null-Packet-Comms-Arduino/tags)
[![Pre-commit](https://img.shields.io/github/actions/workflow/status/CreatingNull/Null-Packet-Comms-Arduino/run-pre-commit.yaml?branch=main&logo=pre-commit&style=flat-square&label=linting)](https://github.com/CreatingNull/Null-Packet-Comms-Arduino/actions/workflows/run-pre-commit.yaml)
[![Read the Docs](https://img.shields.io/readthedocs/null-packet-comms-arduino?style=flat-square&logo=readthedocs)](https://null-packet-comms-arduino.nulltek.xyz)
[![Test](https://img.shields.io/github/actions/workflow/status/CreatingNull/Null-Packet-Comms-Arduino/run-test.yaml?branch=main&logo=github&style=flat-square&label=tests)](https://github.com/CreatingNull/Null-Packet-Comms-Arduino/actions/workflows/run-test.yaml)
[![Build](https://img.shields.io/github/actions/workflow/status/CreatingNull/Null-Packet-Comms-Arduino/run-build.yaml?branch=main&logo=github&style=flat-square&label=build)](https://github.com/CreatingNull/Null-Packet-Comms-Arduino/actions/workflows/run-build.yaml)

This is an arduino library that implements a binary packet-based communication protocol on top of the arduino Serial library.
This wrapper allows for robust generic data transfer between systems,
it is heavily relied on for the [Arduino UOS](https://github.com/CreatingNull/UOS-Arduino) implementation.

For details on this implementation and the API, see the [project documentation](https://null-packet-comms-arduino.nulltek.xyz/en/stable/).
For more information on the NPC protocol and its uses, please see the [protocol documentation](https://wiki.nulltek.xyz/docs/protocols/npc/).

---

## Getting Started

This project is stand-alone and the only requirement is for it to be used in arduino projects.

### Installation

The recommended method to use [this library](https://www.arduino.cc/reference/en/libraries/nullpacketcomms/)
is downloading the latest stable release from the registry using the Arduino Library Manager.

Using the [arduino-cli](https://github.com/arduino/arduino-cli):

```shell
arduino-cli lib install NullPacketComms
```

Using the [arduino-ide](https://github.com/arduino/arduino-ide):

![Installing through IDE](https://github.com/CreatingNull/Null-Packet-Comms-Arduino/blob/main/.resources/Install-via-IDE.gif)

Pre-packed zipped versions of the latest builds can also be obtained from the GitHub build artifacts.
Alternatively, you could manually pack the source and add the library manually, see
[instructions](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries).

### Usage

This library handles communicating and verifying data between the `primary` and
`remote` device, what you do with that data is up to you.
In the [simple_example](examples/simple_example/simple_example.ino) sketch,
we implement a simple accumulating calculator on the arduino that can handle
addition or subtraction operations.

This example sets the:

* `target_` - Target address is used to define the operation.
  * 10 - Perform an addition operation
  * 11 - Perform a subtraction operation
  * 12 - Return the current accumulator value as a signed 16-bit integer.

* `payload` - 1 byte unsigned integer to add or subtract.

Using a `NPC` connection in this manner is implemented in a similar manner to
if you were using raw UART, however instead of using manual `read` and `write`
commands we use `readPacket` and `writePacket`.
The benefit is that we get a closed loop communication where commands are
acknowledged, checksums are verified, and both the `primary` and the `remote`
have some confidence in what is being sent and received.

For more information on the API see the [library documentation](https://null-packet-comms-arduino.nulltek.xyz).

### Source Structure

The source code is written in C++ and contained within the `src/` subdir.
The source code is formatted using `clang-format` specifications.
This is automated via the [pre-commit](https://github.com/pre-commit/pre-commit) framework,
see repo [hooks](https://github.com/CreatingNull/Null-Packet-Comms-Arduino/blob/master/.pre-commit-config.yaml).
The hook's `arduino-lint` dependencies should be installed for the OS, to correctly execute the pre-commit tasks.

The pre-commit action is currently automated by GitHub actions CI, to verify against pushes and pull-requests.

### Testing

The repo includes a test suite built using [googletest](https://github.com/google/googletest) to verify API functionality.
This uses a simple mocked `Arduino.h`
[shim](https://github.com/CreatingNull/Null-Packet-Comms-Arduino/blob/main/.tests/Arduino.cpp)
to 'simulate' hardware response.

The test suite is automated via a GitHub action.
To run the tests locally, you need to install the googletest framework.
You'll also need cmake and a c++ compiler on your development machine.

```shell
cd .tests/
git clone --depth 1 --branch v1.13.0 https://github.com/google/googletest
cd googletest/
cmake CMakeCache.txt
make
sudo make install
cd ..
source env.sh
make
../src/NullPacketComms
```

---

I just do this stuff for fun in my spare time, but feel free to:

[![Support via buymeacoffee](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/nulltek)

---

## License

The source of this repo uses the MIT open-source license,
for details on the current licensing see:
[LICENSE](https://github.com/CreatingNull/Null-Packet-Comms-Arduino/blob/master/LICENSE.md)
or click the badge above.
