# External Control Setup for iiQKA.OS2

This document describes the necessary steps for setting up external control using the **Ethernet KRL Interface** (EKI) and **Robot Sensor Interface** (RSI) on a controller running iiQKA.OS2.
To be able to start control externally or react to errors, wrappers have been implemented depending on either the **Ethernet KRL Interface** (EKI) or **mxAutomation** (mxA) option packages

## Prerequisites

Before configuring the system, ensure you have the following:

- Access to a computer with **iiQWorks.Sim** installed.
- The **Robot Sensor Interface** option package installed in the same project.
- The **Ethernet KRL** or **mxAutomation** option package installed in a project if using one of the wrappers

## Networking Steps

During configuration and setup, connect your computer with iiQWorks.Sim installed to the controller using an Ethernet cable. To enable communication between the two systems, set the IP addresses of the relevant interfaces (KLI on the robot controller and the Ethernet interface on the computer) to be on the same subnet.

Update the IP address in the [`rsi_ethernet.xml`](../krc_setup/iiqka_os2/Config/RobotSensorInterface/Ethernet%20configuration/rsi_ethernet.xml) file with the IP address assigned to the external control computer. This informs the controller where to send data packets during each RSI cycle.

### Example network configuration

Windows computer with iiQWorks.Sim: `172.32.1.150/24`
Robot controller KLI: `172.32.1.147/24`
Robot controller RSI network: `172.32.2.147/24`
Control PC RSI connection: `172.32.2.148/24`
Control PC KLI connection: `172.32.1.148/24` (needed for EKI/mxA wrappers)

## Steps within iiQWorks.Sim

There are several KUKA-specific files located in the [`krc_setup/iiqka_os2`](../krc_setup/iiqka_os2) directory that need to be imported into the iiQWorks.Sim project

### RSI setup

1. Import the [`Program/RSI/`](../krc_setup/iiqka_os2/Program/RSI/) folder to the `KRC/R1/Program` folder (in the **Program** tab in iiQWorks.Sim)
2. Import the [`rsi_joint_pos.rsix`](../krc_setup/iiqka_os2/Config/RobotSensorInterface/Context/rsi_joint_pos.rsix) file under the **Context** field in the **Home** page **Devices** tab under **Option packages > iiQka.RobotSensorInterface**
3. Import the [`rsi_ethernet.xml`](../krc_setup/iiqka_os2/Config/RobotSensorInterface/Ethernet%20configuration/rsi_ethernet.xml) file under **Ethernet configurations** field in the **Home** page **Devices** tab under **Option packages > iiQka.RobotSensorInterface**

For a more complex control scenario, including external axes or I/O, the context and Ethernet configuration files must be modified for the specific use case.

### EKI server setup

1. Perform steps of RSI setup
2. Import the [`EkiKSSinterface.xml`](../krc_setup/iiqka_os2/Config/EthernetKRL/Ethernet%20configuration/EkiKSSinterface.xml) file under the **Context** field in the **Home** page **Devices** tab under **Option packages > iiQka.EthernetKRL**
3. Import the [`Program/EKIServer/`](../krc_setup/iiqka_os2/Program/EKIServer/) folder to the `KRC/R1/Program` folder (in the **Program** tab in iiQWorks.Sim)
4. Modify the `KRC/STEU/Mada/$option.dat` file. Change the `$CHCK_MOVENA` flag to `FALSE` to prevent the system from checking whether `$MOVE_ENABLE` is connected to `$IN[1025]`:
5. To ensure the EKI server runs automatically, edit the `KRC/R1/System/sps.sub` submit interpreter file. Add a call to `SPS_Init()` in the `USER INIT` fold and a call to `SPS_LoopCall()` in the `USER PLC` fold.

### mxA server setup

1. Perform steps of RSI setup
2. Install the mxA option package and select *Protocol: Established*, *Device: UDP* in the *General Settings* of the option package
3. Click *Use default I/O mapping*
4. Perform the manual file manipulation described by [`mxA_TechFunction.add`](../krc_setup/iiqka_os2/TP/mxA%20file%20manipulations/mxA_TechFunction.add) to extend the mxA TechFunction with user defined methods that enable starting the RSI program

Once you have completed these steps, deploy the project onto the controller. After deployment, connect the KRC to the machine you wish to control it with.

## Steps on the SmartHMI

To use external control with the EKI/mxA wrappers, you have to change the operation mode to `EXT` on the SmartHMI. For the simple RSI mode, all other operation modes are working.
