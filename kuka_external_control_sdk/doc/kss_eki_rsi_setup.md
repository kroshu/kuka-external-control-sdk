# External Control Setup for KSS with EKI and RSI

This document describes the necessary steps for setting up external control using the **Ethernet KRL Interface** (EKI) and **Robot Sensor Interface** (RSI) on a controller running **KUKA System Software** (KSS).

## Prerequisites

Before configuring the system, ensure you have the following:

- Access to a computer with **WorkVisual** installed.
- The **Ethernet KRL** option package installed in a project.
- The **Robot Sensor Interface** option package installed in the same project.

## Networking Steps

During configuration and setup, connect your computer with WorkVisual installed to the controller using an Ethernet cable. To enable communication between the two systems, set the IP addresses of the relevant interfaces (KLI on the robot controller and the Ethernet interface on the computer) to be on the same subnet.

1. Check the IP address and subnet mask used by the KRC.
2. Set the same subnet mask and a different IP address on the Ethernet interface of your computer.

Create a new network interface on the KRC for RSI. Ensure the RSI interface is on a different subnet than the KLI. Set the network interface of the computer performing external control to be on the same subnet as the RSI interface.

Update the IP address in the [`kss/krl/SensorInterface/rsi_ethernet.xml`](../kss/krl/SensorInterface/rsi_ethernet.xml) file with the IP address assigned to the external control computer. This informs the controller where to send data packets during each RSI cycle.

## Steps within WorkVisual

There are several KUKA-specific files located in the [`kss/krl/`](../kss/krl/) directory that need to be copied into the WorkVisual project:

1. Copy all files from the [`kss/krl/Program/EKIServer/`](../kss/krl/Program/EKIserver/) and [`kss/krl/Program/RSI/`](../kss/krl/Program/RSI/) directories into `KRC/R1/Program/`.
2. Copy the [`kss/krl/EthernetKRL/EkiKSSinterface.xml`](../kss/krl/EthernetKRL/EkiKSSinterface.xml) file into the `Config/User/Common/EthernetKRL/` directory.
3. Copy all files from the [`kss/krl/SensorInterface/`](../kss/krl/SensorInterface/) directory into the `Config/User/Common/SensorInterface/` directory.

After moving all the files to the correct locations, modify the `KRC/STEU/Mada/$option.dat` file. Change the flag to `FALSE` to prevent the system from checking whether `$MOVE_ENABLE` is connected to `$IN[1025]`.

```krl
; Original setting
BOOL $CHCK_MOVENA=TRUE

; Updated setting
BOOL $CHCK_MOVENA=FALSE
```

To ensure the EKI server runs automatically, edit the `KRC/R1/System/sps.sub` submit interpreter file. Add a call to `SPS_Init()` in the `USER INIT` fold and a call to `SPS_LoopCall()` in the `USER PLC` fold.

Once you have completed these steps, deploy the project onto the controller. After deployment, connect the KRC to the machine you wish to control it with.

## Steps on the SmartHMI

To use external control, you have to change the mode to `EXT` on the SmartHMI.
