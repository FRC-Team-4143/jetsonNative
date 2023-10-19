cmake_minimum_required(VERSION 3.5)
project(jetsonNative) # Project Name Here

find_package(wpilib REQUIRED)

add_compile_options(-Wno-psabi)

add_executable(jetsonNative Robot.cpp) # executable name as first parameter
add_library(hook SHARED hook.c)
target_include_directories(jetsonNative PUBLIC /usr/local/include/ /usr/local/include/ctre)
target_link_libraries(jetsonNative wpilibc REVLib CTRE_Phoenix CTRE_PhoenixCCI CANBridge)  # wpilibNewCommands cameraserver ntcore cscore wpiutil
