cmake_minimum_required(VERSION 3.20)

# Connect the toolchain file
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-none-eabi.cmake)

project(cav-x C CXX ASM)

# Tell the system where headers live
include_directories(core/inc drivers/inc)

message(STATUS "cav-x Framework: Build System Online")

# Define H-7 Chip
add_definitions(-DSTM32H753XX)

# Source files
target_include_directories(cav-x PUBLIC
    drivers/external/csmis_device_h7/Include 
    drivers/external/CSMIS_5/CMSIS/Include
    core/inc 
    drivers/inc
)