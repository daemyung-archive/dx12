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
vcpkg install glfw3:x64-windows
vcpkg install spdlog:x64-windows
```

### Generate Project Files

```
mkdir build
cmake . -B build -DCMAKE_TOOLCHAIN_FILE=${VCPKG_DIR}/script/buildsystem/vcpkg.cmake
```
