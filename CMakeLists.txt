#
# This file is part of the "dx12" project
# See "LICENSE" for license information.
#

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(dx12 VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_DEMO "build dx12 demo" ON)
option(BUILD_TEST "build dx12 test" ON)

add_library(dx12
STATIC
    include/glue.h
    include/dxgi.h
    include/d3d12.h
    src/dxgi.cpp
    src/d3d12.cpp
)

target_include_directories(dx12
PUBLIC
    include
)

target_compile_options(dx12
PUBLIC
    -x objective-c++
)

target_link_libraries(dx12
PUBLIC
    "-framework QuartzCore"
    "-framework Metal"
)

set_target_properties(dx12
PROPERTIES
    CXX_STANDARD 17
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
)

if(BUILD_DEMO)

add_executable(dx12_demo
    demo/main.cpp
)

target_link_libraries(dx12_demo
    dx12
)

endif()
