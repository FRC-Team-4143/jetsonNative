#!/bin/sh

./canableStart.sh
export HALSIM_EXTENSIONS="libhalsim_ds_socket.so:libCANBridge.so"
LD_LIBRARY_PATH=build/jni/release LD_PRELOAD=libbuild/libhook.so java -jar build/libs/jetsonNative.jar

