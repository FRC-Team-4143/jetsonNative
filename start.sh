#!/bin/sh

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

