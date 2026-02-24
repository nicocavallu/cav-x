# CAV-X Framework
**Target Hardware:** STM32H753XX (ARM Cortex-M7)

## Project Overview
CAV-X is a custom, modular firmware framework built from scratch using CMake and Ninja. It avoids heavy IDE bloat for a professional, CLI-first development experience.

## Build Requirements
* **WSL2 (Ubuntu)**
* **ARM GNU Toolchain** (gcc-arm-none-eabi)
* **CMake** (v3.20+)
* **Ninja**

## How to Build
1. Clone the repo with submodules:
   `git clone --recursive <repo-url>`
2. Configure:
   `mkdir build && cd build && cmake -G Ninja ..`
3. Compile:
   `ninja`

## Memory Map (STM32H753)
* **Flash:** 2MB @ `0x08000000`
* **RAM (D1):** 512KB @ `0x24000000`

## External Dependencies
This project uses Git Submodules for hardware abstraction:
* `drivers/external/cmsis_device_h7`: ST Device Headers
* `drivers/external/CMSIS_5`: ARM Core Headers