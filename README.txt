#Proof of concept requires:
#libCANBridge.so from https://github.com/FRC-Team-4143/CANBridge/tree/4143
#(arm64 binary included in libbuild dir)

#build libhook.so with cmake: I can't figure out gradle cpp-library with aarch64
cd libbuild
cmake ..
make

copy either build.gradle.c++ or build.gradle.java to build.gradle

#build with:
./gradlew installFrcUserProgramReleaseExecutable  # for C++
./gradlew build		# for JAVA

#copy libraries to install dir
cp libbuild/*.so build/install/frcUserProgram/release/lib/   # for C++
cp libbuild/*.so build/jni/release  				# for JAVA



# run canableStart.sh to get SocketCAN going
./canableStart.sh

# must run this to load simulation driverstation code
export HALSIM_EXTENSIONS="libhalsim_ds_socket.so:libCANBridge.so"

# must preload libhook.so to cause HAL_CreateSimDevice to always return zero for SPARK MAX
# REV libraries use this to determine if they should actually interact with hardware or not

#execute with
#cd ./build/install/frcUserProgram/release/lib/  # for C++
#LD_LIBRARY_PATH=. LD_PRELOAD=libhook.so ./frcUserProgram  # for C++

#for JAVA
# have to build/jni/release in path
LD_LIBRARY_PATH=build/jni/release LD_PRELOAD=libbuild/libhook.so java -jar build/libs/jetsonNative.jar




SAMPLE WORKING OUTPUT:

HAL Extensions: Attempting to load: libhalsim_ds_socket
DriverStationSocket Initializing.
DriverStationSocket Initialized!
HAL Extensions: Successfully loaded extension
HAL Extensions: Attempting to load: libCANBridge
registering canbridge
SocketCANDeviceThread()
can0
SocketCAN thread started
CANBridge_Register status: CandleRun()
0
HAL Extensions: Successfully loaded extension

********** Robot program starting **********
Not loading CameraServerShared
NT: could not open persistent file 'networktables.json': No such file or directory (this can be ignored if you aren't expecting persistent values)
NT: Listening on NT3 port 1735, NT4 port 5810
HAL_CreateSimDevice: SPARK MAX [1]
skipping orig HAL_CreateSimDevice
HAL_CreateSimDevice: CANMotor:Talon SRX[3]
HAL_CreateSimDevice: CANAIn:Talon SRX[3]/Analog In
HAL_CreateSimDevice: CANDutyCycle:Talon SRX[3]/Pulse Width Input
HAL_CreateSimDevice: CANEncoder:Talon SRX[3]/Quad Encoder
HAL_CreateSimDevice: CANDIO:Talon SRX[3]/Fwd Limit
HAL_CreateSimDevice: CANDIO:Talon SRX[3]/Rev Limit
HAL_CreateSimDevice: CANMotor:Talon SRX[2]
HAL_CreateSimDevice: CANAIn:Talon SRX[2]/Analog In
HAL_CreateSimDevice: CANDutyCycle:Talon SRX[2]/Pulse Width Input
HAL_CreateSimDevice: CANEncoder:Talon SRX[2]/Quad Encoder
HAL_CreateSimDevice: CANDIO:Talon SRX[2]/Fwd Limit
HAL_CreateSimDevice: CANDIO:Talon SRX[2]/Rev Limit

********** Robot program startup complete **********
Default DisabledPeriodic() method... Override me!
Default RobotPeriodic() method... Override me!
Default SimulationPeriodic() method... Override me!
[phoenix] CANbus Connected: can0
	
[phoenix] CANbus Network Up: can0
	
[phoenix] CANbus Failed Bring-up: can0
	
[CAN SPARK MAX] IDs: 1, Unable to retrieve SPARK MAX firmware version. Please verify the deviceID field matches the configured CAN ID of the controller, and that the controller is connected to the CAN Bus. 
[phoenix] Library initialization is complete.
	
[phoenix-diagnostics] Server 2024.0.2 (Oct 18 2023, 15:38:59) running on port: 1250
	


