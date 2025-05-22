# KSS Robot Interface

This document describes all KSS-specific functionality of the SDK.

The SDK uses the **Robot Sensor Interface** (RSI) option package for controlling the robot. If you have followed the [setup guide for KSS](kss_eki_setup.md), you already have this installed. However, the guide also instructs you to install EKI, which isn't necessary if you only want to control the robot from an external system.

There are two versions of the KSS-specific robot interface available: one that offers functionality solely for controlling the robot, and another that also communicates with the robot controller in a non-real-time manner, enabling additional functionality (e.g., receiving status updates, changing the RSI cycle time).

## Basic Robot Interface

The basic implementation offers no additional functionality beyond what is specified by the `IRobot` interface. However, the following methods are not supported, despite being listed in the interface:

- `StartControlling()`
- `StartMonitoring()`
- `StopMonitoring()`
- `CreateMonitoringSubscription(std::function<void(BaseMotionState&)> callback)`
- `CancelMonitoringSubscription()`
- `SwitchControlMode(ControlMode control_mode)`
- `RegisterEventHandler(std::unique_ptr<EventHandler>&& event_handler)`

Since the `StartControlling` method is not supported, you might wonder how to start controlling the robot. The timeout before receiving the very first motion state from the robot controller should be set to a longer period of time. Once the program starts waiting for this motion state, you should manually start one of the RSI programs (i.e., `rsi_joint_pos_4ms` or `rsi_joint_pos_12ms.src`) previously deployed to the robot controller by selecting it on the SmartHMI. Once the first message from RSI arrives at the external control system, you will be able to control the robot.

If you wish to look into the implementation, you may want to start with [`robot_interface.h`](../kss/include/kuka/external-control-sdk/kss/rsi/robot_interface.h).

## Enhanced Robot Interface

The enhanced robot interface is derived from the basic one. This means that controlling happens the same way it did before; however, you will not have to start the KRL program manually, since most methods in the `IRobot` interface are implemented in this version. The exceptions are:

- `StartMonitoring()`
- `StopMonitoring()`
- `CreateMonitoringSubscription(std::function<void(BaseMotionState&)> callback)`
- `CancelMonitoringSubscription()`

In short, monitoring is not yet supported. However, there are methods that are only available for KSS with EKI:

- `TurnOnDrives()`: Turns the robot's drives on.
- `TurnOffDrives()`: Turns the robot's drives off.
- `SetCycleTime(CycleTime cycle_time)`: Set the cycle time of RSI (4ms and 12ms).
- `RegisterEventHandlerExtension(std::unique_ptr<IEventHandlerExtension>&& extension)`: There are events that are not meant to be handled by the event handler specified in the generic interface. This method enables the client to react to those events as well.
- `RegisterStatusResponseHandler(std::unique_str<IStatusUpdateHandler>&& handler)`: The EKI server sends status updates whenever it has spare resources and its state has changed. This method enables the client to react to these updates.

All other methods work as described in the generic `IRobot` interface description.

If you wish to look into the implementation, you may want to start with [`robot_interface.h`](../kss/include/kuka/external-control-sdk/kss/eki/robot_interface.h).

## Convenience Wrapper Class

Although there are currently only two versions of the robot interface for the KSS system, more may be developed in the future. To provide a unified class for using all different versions, a wrapper class was created. This class instantiates the appropriate version of the robot interface based on the configuration passed to it and forwards all method calls to the underlying implementation.

If you wish to look into the implementation, you may want to start with [`robot.h`](../kss/include/kuka/external-control-sdk/kss/robot.h).
