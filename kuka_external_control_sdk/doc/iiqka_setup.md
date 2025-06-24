<h2>Environment setup for KUKA.iiQKA.ExternalAPI.Control</h2>
The purpose of this documentation is to provide the user with the necessary steps to ensure that the system is in a valid state for using the KUKA.iiQKA.ExternalAPI.Control toolbox.
<h3>KONI IP configuration</h3>
Setting up the network configuration is as simple as configuring the IP address on the KONI interface.

One way to do this is by connecting the controller to the same router the client machine is connected to, on the XF7 port. The controller then should get an IP address on KONI through DHCP with the default configuration. You can view this IP address on the smartpad in the System Settings > Network > KONI tab.

The second method is to first connect the client machine directly to the KONI interface on the XF7 port. In this scenario, both the KRC and the client machine have to have manual IP addresses configured. For the KRC it can be done in the System Settings > Network > KONI tab by choosing the "manual" radio button.

Note that if the KONI IP is changed once, and modified later, the KRC has to be rebooted for the changes to take effect.

<h3> SPOC </h3>

The name SPOC stands for "Single Point of Control". This is the component that ensures that the robot cannot be worked on by multiple clients at once. It can mean anything from changing some safety configurations to explicitly moving the robot. The SPOC permission is automatically claimed by the UI, so to use the toolbox, it has to be released first by clicking on the 'user' icon on the top right corner of the smartpad, and pressing the release button.

If there is no active client (and there shouldn't be, since the smartpad just released the permission), then the first 'StartControlling' call from the client library, or the first 'OpenControlChannel' grpc call will register the SPOC ID of the external service, and request the permission. If successful, the control session can begin in 3 seconds.

After the control session is over, the SPOC permission is released automatically. Monitoring is independent from the SPOC, and so can be performed in parallel to other operations on the smartpad, such as jogging.

<h3> OP mode and Safety </h3>

External control is only allowed in AUT or T1 mode. Currently this can only be set from the UI right next to the icons indicating the number of warnings and errors. In T1 mode, the enabling button needs to be held down as long as the robot movements from the external client are to be executed. In AUT mode, the robot movement is executed automatically.

The enabled safety configurations and limits also apply to external movement. Any violations will terminate the external session, including pressing the emergency stop button.

<h2> Using KUKA.iiQKA.ExternalAPI.Control </h2>

After successfully setting up the environment, there are two ways two use the product.

The easier way is to use the SDK we provide on top of the toolbox, you can check the [documentation](../../README.md) of it to get started.

But there is a low-level approach, too: one could use the protos that define the messages being sent. They are provided with the kuka-external-control-sdk-protobuf library installed with the SDK. To compile the proto files and generate the ones needed for development check out the instructions for your desired programming language [here](https://github.com/protocolbuffers/protobuf#readme).

To see how to use the raw protos for a general control/monitoring, check out the examples in the SDK documentation. The logic is the same, only the calls are different. To see how the SDK calls are mapped to the raw proto calls, check out [this file](Raw_proto_mapping.md).
The only requirement is to receive and send from/to the given addresses and ports via gRPC and UDP and fulfill the real-time requirements in case of the UDP communication.

<span style="color:red;font-weight:700;font-size:14px">One thing you have to be aware of is that in the received motion states, the torque values have different sign than the client is expected to send out in each tick during torque control. (To move a joint in the positive direction, a positive torque is needed, however the motion state will contain a negative measured torque in this cases due to internal conventions).</span>
