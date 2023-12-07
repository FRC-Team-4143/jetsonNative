cmake_minimum_required(VERSION 3.5)
project(libhook) # Project Name Here

add_library(hook SHARED hook.c)

TARGET_LINK_LIBRARIES(hook pigpio)