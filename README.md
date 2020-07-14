# DX12

## Overview

**DX12** is a layered implement of DirectX 12, that is build on Metal on macOS.

## Features

* [ ] DirectX Graphics Infrastructure
* [ ] DirectX 12
* [X] COM Smart Pointer

## Requirements

* [CMake](https://github.com/Kitware/CMake)
* [Vcpkg](https://github.com/Microsoft/vcpkg)

## Build

### Install dependencies

```
vcpkg install fmt
vcpkg install glslang
vcpkg install spirv-tools
vcpkg install spirv-cross
vcpkg install glfw3
vcpkg install spdlog
```

### Generate Project Files

```
mkdir build
cmake . -B build -DCMAKE_TOOLCHAIN_FILE=${VCPKG_DIR}/script/buildsystem/vcpkg.cmake
```
