# External Control Setup for KSS

This document describes the necessary steps for setting up external control using the **Robot Sensor Interface** (RSI) option package on a controller running **KUKA System Software** (KSS).
To be able to start control externally or react to errors, wrappers have been implemented depending on either the **Ethernet KRL Interface** (EKI) or **mxAutomation** (mxA) option packages

## Prerequisites

Before configuring the system, ensure you have the following:

- Access to a computer with **WorkVisual** installed.
- The **Robot Sensor Interface** option package installed in the same project.
- The **Ethernet KRL** or **mxAutomation** option package installed in a project if using one of the wrappers

## Networking Steps

During configuration and setup, connect your computer with WorkVisual installed to the controller using an Ethernet cable. To enable communication between the two systems, set the IP addresses of the relevant interfaces (KLI on the robot controller and the Ethernet interface on the computer) to be on the same subnet.

Create a new network interface on the KRC for RSI. Ensure the RSI interface is on a different subnet than the KLI. To add a new network interface on the robot controller, follow these steps:

1. Select at least the *Expert* user group.
2. Navigate to *Main menu* &rarr; *Start-up* &rarr; *Network configuration*.
3. Click on the *Advanced...* button.
4. At the bottom, click *Add interface*.
5. Select the new interface, which will be listed as *virtual6 (virtual)* by default.
6. Select Mixed IP address and keep the default settings:
   1. Receiving task: Target subnet
   2. Real-time receiving Task: UDP
7. Choose an IP address that is on a different subnet than the KLI interface
   1. Default gateway: leave it empty
   2. Windows interface checkbox should NOT be checked
8. At the bottom, click *Save*.
9.  Restart the robot control controller to ensure configuration changes are applied.

Update the IP address in the [`rsi_ethernet.xml`](../krc_setup/kss/Config/User/Common/SensorInterface/rsi_ethernet.xml) file with the IP address assigned to the external control computer. This informs the controller where to send data packets during each RSI cycle.

Set the network interface of the computer performing external control to be on the same subnet as the RSI interface. If you are using the EKI or mxA wrappers, make sure that the computer for external control can reach both the KLI and RSI interfaces. The best way to do this is to assign multiple IP addresses to one physical network connection.

### Example network configuration

Windows computer with WorkVisual: `172.32.1.150/24`
Robot controller KLI: `172.32.1.147/24`
Robot controller RSI network: `172.32.2.147/24`
Control PC RSI connection: `172.32.2.148/24`
Control PC KLI connection: `172.32.1.148/24` (needed for EKI/mxA wrappers)

## Steps within WorkVisual

There are several KUKA-specific files located in the [`krc_setup/kss`](../krc_setup/kss) directory that need to be copied into the WorkVisual project

### RSI setup

1. Copy all files from the [`Config/User/Common/SensorInterface/`](../krc_setup/kss/Config/User/Common/SensorInterface/) directory into the `Config/User/Common/SensorInterface/` directory.
2. Copy all files from the [`Program/RSI/`](../krc_setup/kss/KRC/R1/Program/RSI/) directories into `KRC/R1/Program/`.

For a more complex control scenario including external axes or I/O-s, the context and ethernet configuration files have to be modified for the specific use case.

### EKI server setup

1. Perform steps of RSI setup
2. Copy the [`EkiKSSinterface.xml`](../krc_setup/kss/Config/User/Common/EthernetKRL/EkiKSSinterface.xml) file into the `Config/User/Common/EthernetKRL/` directory.
3. Copy all files from the [`Program/EKIServer/`](../krc_setup/kss/KRC/R1/Program/EKIserver/) directories into `KRC/R1/Program/`.
4. Modify the `KRC/STEU/Mada/$option.dat` file. Change the `$CHCK_MOVENA` flag to `FALSE` to prevent the system from checking whether `$MOVE_ENABLE` is connected to `$IN[1025]`.
5. To ensure the EKI server runs automatically, edit the `KRC/R1/System/sps.sub` submit interpreter file. Add a call to `SPS_Init()` in the `USER INIT` fold and a call to `SPS_LoopCall()` in the `USER PLC` fold.

### mxA server setup

1. Perform steps of RSI setup
2. Install the mxA option package with mode UDP selected (this only connects the I/O-s for the UDP setup)
3. Perform the manual file manipulations described by the following files:
   1. [`UDPConfig`](../krc_setup/kss/KRC/R1/TP/mxA%20file%20manipulations/UDPConfig) to fully change to UDP mode
   2. [`mxA_TechFunction.add`](../krc_setup/kss/KRC/R1/TP/mxA%20file%20manipulations/mxA_TechFunction.add) to extend the mxA TechFunction with user defined methods that enable starting the RSI program

Once you have completed these steps, deploy the project onto the controller. After deployment, connect the KRC to the machine you wish to control it with.

## Steps on the SmartHMI

To use external control with the EKI/mxA wrappers, you have to change the operation mode to `EXT` on the SmartHMI. For the simple RSI mode, all other operation modes are working.
