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
- `RegisterStatusResponseHandler(std::unique_str<IStatusUpdateHandler>&& handler)`: The EKI or mxA server sends status updates whenever it has spare resources and its state has changed. This method enables the client to react to these updates.

All other methods work as described in the generic `IRobot` interface description.

If you wish to look into the implementation, you may want to start with [`robot_interface.h`](../kss/include/kuka/external-control-sdk/kss/eki/robot_interface.h).

## Convenience Wrapper Class

To provide a unified class for using all different versions, a wrapper class was created. This class instantiates the appropriate version of the robot interface based on the configuration passed to it and forwards all method calls to the underlying implementation.

If you wish to look into the implementation, you may want to start with [`robot.h`](../kss/include/kuka/external-control-sdk/kss/robot.h).

## Configurable Motion-State XML Parsing

The KSS parser is configuration-driven. Instead of hard-coding `RIst/AIPos/EIPos/A1..A6/E1..E6`, the XML fields are selected by `Configuration::motion_state_xml_config` (`MotionStateXmlConfiguration`).

### Configuration model

`MotionStateXmlConfiguration` defines:

- **Joint identifier mapping** (`joint_fields`): each entry binds a `joint_identifier` (from `JointConfiguration::name`) to an XML element/attribute pair.
- **Per-joint signal selection** (`signal_type`): each joint field can target `position`, `velocity`, or `torque`.
- **TCP pose configuration** (`cartesian`): enable/disable Cartesian parsing and configure element/attribute names.
- **GPIO mapping** (`gpio_xml_element`, `gpio_xml_attributes`): map state GPIO fields to XML attributes.
- **Field ordering** (`field_order`): parsing order is explicit and validated; supported types are `CARTESIAN`, `JOINT`, `DELAY`, `GPIO`, `IPOC`.

If `motion_state_xml_config` is not provided, the legacy RSI layout is generated automatically to keep existing applications compatible.

### Initialization-time validation

`MotionState` builds a parse plan once during construction and validates that:

- every referenced joint identifier exists
- all required XML names are non-empty
- GPIO mapping count matches configured GPIO states
- `field_order` indices are in range
- `field_order` contains each configured joint/GPIO entry exactly once
- `field_order` contains exactly one `DELAY` and one `IPOC`
- `CARTESIAN` appears iff Cartesian parsing is enabled

Invalid configurations fail fast with `std::invalid_argument` before runtime control starts.

### Runtime parsing flow (real-time safe)

At runtime (`MotionState::CreateFromXML`):

1. No parser metadata is built.
2. The precomputed parse order is executed.
3. Each step locates configured element/attribute values and parses directly from the incoming buffer.
4. Joint units are converted using `JointConfiguration::type`:
   - revolute position/velocity: degrees -> radians
   - prismatic position/velocity: millimetres -> metres
   - torque: parsed as-is (for now)

No dynamic memory allocation is performed after `MotionState` and `ControlSignal` objects are created; all lookup tables and mappings are prebuilt at initialization.

### Example configurations

#### 1. Legacy-compatible layout (implicit default)

```cpp
kuka::external::control::kss::Configuration cfg;
cfg.joint_configs = {
  {"joint_1", JointConfiguration::Type::REVOLUTE, false},
  {"joint_2", JointConfiguration::Type::REVOLUTE, false},
};
// cfg.motion_state_xml_config not set -> default RSI layout is used.
```

Expected XML fragment:

```xml
<RIst X="..." Y="..." Z="..." A="..." B="..." C="..."/>
<AIPos A1="..." A2="..."/>
<Delay D="..."/>
<IPOC>...</IPOC>
```

#### 2. Mixed per-joint signal selection, custom identifiers, no TCP

```cpp
MotionStateXmlConfiguration xml_cfg;
xml_cfg.cartesian.enabled = false;
xml_cfg.joint_fields = {
  {"joint_1", MotionStateSignalType::POSITION, "Joints", "j1_pos"},
  {"joint_1", MotionStateSignalType::VELOCITY, "Joints", "j1_vel"},
  {"joint_2", MotionStateSignalType::TORQUE, "Forces", "j2_torque"},
};
xml_cfg.delay_xml_element = "Meta";
xml_cfg.delay_xml_attribute = "delay";
xml_cfg.ipoc_xml_element = "Cycle";
xml_cfg.field_order = {
  {MotionStateXmlFieldType::JOINT, 0},
  {MotionStateXmlFieldType::JOINT, 1},
  {MotionStateXmlFieldType::JOINT, 2},
  {MotionStateXmlFieldType::DELAY, 0},
  {MotionStateXmlFieldType::IPOC, 0},
};
cfg.motion_state_xml_config = xml_cfg;
```

Expected XML fragment:

```xml
<Joints j1_pos="..." j1_vel="..."/>
<Forces j2_torque="..."/>
<Meta delay="..."/>
<Cycle>...</Cycle>
```

#### 3. Custom ordering with GPIO and Cartesian fields

```cpp
xml_cfg = MotionStateXmlConfiguration{};
xml_cfg.joint_fields = {
  {"joint_1", MotionStateSignalType::POSITION, "Joints", "j1_pos"},
  {"joint_2", MotionStateSignalType::VELOCITY, "Joints", "j2_vel"},
};
xml_cfg.cartesian.enabled = true;
xml_cfg.cartesian.xml_element = "Tcp";
xml_cfg.cartesian.xml_attributes = {"px", "py", "pz", "ra", "rb", "rc"};
xml_cfg.delay_xml_element = "Meta";
xml_cfg.delay_xml_attribute = "delay";
xml_cfg.gpio_xml_element = "Io";
xml_cfg.gpio_xml_attributes = {"enable", "mode"};
xml_cfg.ipoc_xml_element = "Cycle";
xml_cfg.field_order = {
  {MotionStateXmlFieldType::JOINT, 0},
  {MotionStateXmlFieldType::JOINT, 1},
  {MotionStateXmlFieldType::GPIO, 0},
  {MotionStateXmlFieldType::GPIO, 1},
  {MotionStateXmlFieldType::CARTESIAN, 0},
  {MotionStateXmlFieldType::DELAY, 0},
  {MotionStateXmlFieldType::IPOC, 0},
};
cfg.motion_state_xml_config = xml_cfg;
```

Example XML fragment:

```xml
<Joints j1_pos="..." j2_vel="..."/>
<Io enable="1" mode="2"/>
<Tcp px="..." py="..." pz="..." ra="..." rb="..." rc="..."/>
<Meta delay="..."/>
<Cycle>...</Cycle>
```

This is valid because every configured joint field (`JOINT`) and GPIO attribute (`GPIO`), plus
`DELAY` and `IPOC`, appears exactly once in `field_order`.
