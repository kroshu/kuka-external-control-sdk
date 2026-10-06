# KUKA.iiQKA.ExternalAPI.Control SDK

KUKA.iiQKA.ExternalAPI.Control is an option package on iiQKA 1.2. It allows you to connect remotely to a KUKA KR C5 Micro running this option package and externally control an LBR iisy 3, LBR iisy 11, or LBR iisy 15.

This SDK makes it easy to develop client applications for externally controlling iiQKA robots.

## Requirements

- Linux as the operating system
- A compiler that supports the C++17 standard.
- Installation of the following packages/components:
  - cmake
  - GNU/g++ compiler
  - OpenSSL
  - Protobuf
  - PkgConfig
  - gRPC C++ module
  - grpc_cpp_plugin

Installation of the packages for the most used Linux operating systems can be done with the following commands:

- Ubuntu (20.04, 22.04) & Debian (bullseye, bookworm):

  ```bash
  apt install -y cmake build-essential pkg-config libssl-dev protobuf-compiler-grpc libgrpc++-dev
  ```

- RHEL & almalinux 8:

  ```bash
  dnf install -y https://repo.almalinux.org/almalinux/almalinux-release-synergy-latest-8.noarch.rpm
  dnf install --enablerepo=powertools -y protobuf-devel cmake gcc-c++ openssl-devel grpc-devel grpc-plugins
  ```

- RHEL & almalinux 9:

  ```bash
  dnf install -y https://repo.almalinux.org/almalinux/almalinux-release-synergy-latest-9.noarch.rpm
  dnf install --enablerepo=crb -y protobuf-devel cmake gcc-c++ openssl-devel grpc-devel grpc-plugins
  ```

- Fedora (38, 39):

  ```bash
  dnf install -y cmake gcc-c++ protobuf-devel grpc-devel openssl-devel
  ```

## Build and installation

To optimize the performance of the generated protobuf libraries, you can extend all .proto files with the following line:

```txt
option optimize_for = LITE_RUNTIME;
```

This was omitted from the sdk for backward-compatibility reasons, as older versions of the protobuf library does not support this.

If all requirements are met, the SDK can be installed with cmake:

```bash
cd <clone of this repository>
mkdir build && cd build
cmake ..
make install
```

This will install the necessary headers and the library itself, which can then be used from the client application's CMake project.
A separate shared library (kuka-external-control-sdk-protobuf) is defined and exported for the generated protobuf object to allow the client to bypass the client library and use the raw protos, if they wish to use a lower level API instead of a fully fledged SDK.

An example CMakeLists.txt for a simple application with a single source file would look like this:

```cmake
cmake_minimum_required(VERSION 3.13)

project(${DEBIAN_PROJECT_NAME} VERSION ${DEBIAN_PROJECT_VERSION})

# Project dependencies
find_package(kuka-external-control-sdk REQUIRED)

add_executable(client_app client_application.cc)

target_link_libraries(client_app kuka-external-control-sdk)
```

By default, the kuka-external-control-sdk library is installed under `~/.local/lib`, and the config is under `~/.local/lib/cmake`, so make sure to add it to the CMAKE_PREFIX_PATH to be able to find the package.

### iiQKA-Specific Robot Interface

The iiQKA Robot class introduces OS specific features. It uses gRPC for non-real-time communication such as configuration and state management operations, and UDP for the real-time part - controlling and monitoring.

#### Structure

The extra method of the Robot class providing the specific interface:

- _SetQoSProfile(qos configuration)_ : Sets the Quality of Service (QoS) configuration for external control on the controller. If successful, the next session will be started with this configuration.

With this _SetQoSProfile_ function the user can set the QoS configuration, which is detailed later.

#### Configuration

Before creating the iiQKA-specific Robot object, an initial configuration has to be provided via the namespaced Configuration class. It should contain the IP addresses of the KRC5 Micro on the KONI interface and the IP address of the client machine. It's also possible to enable a secure version of robot control by setting the is_secure flag to true.

During secure controlling, the UDP packets are by default sent and received through a secure DTLS layer. So the user has to provide a certificate and private key and set the path of these files in the configuration. For generating a certificate and a private key see an example [here](https://stackoverflow.com/a/10176685) or check out the [official documentation](https://www.openssl.org/docs/manmaster/man1/openssl.html).

The currently supported control modes are:

- Joint position control
- Joint impedance control
- Joint torque control

Aside from these, the configuration also contains values that can't be modified.
These are the:

1. Port numbers. During controlling, the packets are received on the 44444 port, and on the 44446 port during monitoring.
2. Cycle time. The cycle time is 4 milliseconds, or 250 Hz. This is enforced by the motion layer and can't be higher or lower.
3. Multicast IP address for monitoring, which is 239.255.123.250.

#### QoS configuration

Since the UDP protocol is unreliable, we have created a simple QoS profile which monitors the number of lost packets in a given timeframe, and the number of consecutively lost packets. These are measured on the controller side and used to terminate the connection when the network quality is not suitable for external robot control.

The following parameters of the profile can be tailored to the specific use case:

- number of consecutively lost packets - _default = 2_
- number of lost packets allowed in a timeframe - _default = 3_
- the timeframe - _default = 200 ms_

If no QoS profile is set at all before the call to StartControlling, a default profile will be used internally.
It's possible to update the settings using the _SetQoSProfile_ call of the SDK. The configured values should meet the given constraints:

- The user cannot set the consequent packet losses to be bigger than 5, therefore external control always stops within 20 ms of a connection loss.
- The user cannot set the timeframe/packet loss ratio to be smaller than 40 to disallow too lossy connections.
- The user cannot set the allowed packet losses in a timeframe to be bigger than 25 to disallow too many lost packets in a concentrated part of a larger timeframe.
- The user cannot set the timeframe to be bigger than 1 hour.
- If the user tries to set an invalid QoS profile, external control cannot be started until a valid profile is set.
- If the user would like to set a QoS profile that does not allow any packet losses, only the consecutively lost packets should be set to 0!

If any of the above requirements is violated, the QoS profile will not be set, and the user will have to provide a valid profile to be able to start controlling the robot. This applies only if the QoS configuration is invalid.

## How to use the SDK from code

Here's a simple example of how the SDK can be used for controlling an iiQKA robot.

```cpp
#include "kuka/external-control-sdk/iiqka/sdk.h"

int main(int argc, char const *argv[]) {
  // Configure general setup - IP addresses
  kuka::external::control::iiqka::Configuration eci_config;
  eci_config.client_ip_address = "127.0.0.1"; // client ip address
  eci_config.koni_ip_address = "127.0.0.1"; // KRC IP address

  // Create interface
  kuka::external::control::iiqka::Robot rob_if(eci_config);
  Status setup_ret = rob_if->Setup();

  // ...
}
```

The above code creates a configuration which will be used for creating the instance of the client library's Robot object. After that, the sockets used for communicating with the robot can be created, allowing us to start controlling or monitoring later. Note that the configuration with which the Robot instance is created can not be modified later for the given object.

The next step is to call StartControlling and create a control loop. It's recommended to always check the returned status of each operation, which we omitted to make the example concise.

```cpp
rob_if->StartControlling(kuka::external::control::ControlMode::JOINT_POSITION_CONTROL);

// Degree of freedom
size_t dof = 6;
kuka::external::control::BaseMotionState actual_state(dof); // Motion state filled when received from the controller.

while (true) {
  rob_if->ReceiveMotionState(/* timeout */);

  actual_state = rob_if->GetLastMotionState(); // gives access the current position, velocity or torques values

  // ... calculate next control signal based on the actual state

  rob_if->GetControlSignal().AddJointPositionValues(/* calculated joint position values with begin and end iterators*/);
  rob_if->SendControlSignal(); // or call rob_if->SwitchControlMode() instead to change the control mode, or StopControlling() to stop the control session.
}
```

Examples for controlling the robot and starting a monitoring session also come with the SDK. The IP addresses of the controller and the client machine have to be configured in the code, and for the controlling example, it is recommended to set the robot axes into a 'candle' position at the start to `{A1: 0°, A2: -90°, A3: 0°, A4: 0°, A5: 0°, A6: 0°}`.

because it's executing a sine movement.

These examples can be tried out by building their CMake project after installing the SDK library.

## License

The library is licensed under Apache-2.0.
