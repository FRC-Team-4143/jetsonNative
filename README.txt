# run canableStart.sh to get SocketCAN going
./canableStart.sh

# must run this to load simulation driverstation code

export HALSIM_EXTENSIONS="libhalsim_ds_socket.so"

# must preload libhook.so to cause HAL_CreateSimDevice to always return zero
# REV libraries use this to determine if they should actually interact with hardware or not

LD_PRELOAD=/home/ubuntu/jetsonNative/build/libhook.so ./jetsonNative




SAMPLE WORKING OUTPUT:


HAL Extensions: Attempting to load: libhalsim_ds_socket
DriverStationSocket Initializing.
DriverStationSocket Initialized!
HAL Extensions: Successfully loaded extension
registering canbridge
SocketCANDeviceThread()
can0
CandleRun()
SocketCAN thread started
CANBridge_Register status: 0

********** Robot program starting **********
Not loading CameraServerShared
NT: Listening on NT3 port 1735, NT4 port 5810

********** Robot program startup complete **********
Default DisabledPeriodic() method... Override me!
Default RobotPeriodic() method... Override me!
Default SimulationPeriodic() method... Override me!
[phoenix] CANbus Connected: can0
	
[phoenix] CANbus Network Up: can0
	
[phoenix] CANbus Failed Bring-up: can0
	
[CAN SPARK MAX] IDs: 1, Unable to retrieve SPARK MAX firmware version. Please verify the deviceID field matches the configured CAN ID of the controller, and that the controller is connected to the CAN Bus. 
NT: Got a NT3 connection from 192.168.0.196 port 55575
NT: CONNECTED NT3 client 'NT3@192.168.0.196:55575' (from 192.168.0.196:55575)
[phoenix] Library initialization is complete.
	
[phoenix-diagnostics] Server 2023.1.0 (May 18 2023, 23:43:59) running on port: 1250

