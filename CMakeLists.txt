#
# This file is part of the "dx12" project
# See "LICENSE" for license information.
#

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(dx12 VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_DEMO "build dx12 demo" ON)
option(BUILD_TEST "build dx12 test" ON)

find_package(fmt CONFIG REQUIRED)
find_package(glslang CONFIG REQUIRED)
find_package(SPIRV-Tools CONFIG REQUIRED)
find_package(spirv_cross_core CONFIG REQUIRED)
find_package(spirv_cross_glsl CONFIG REQUIRED)
find_package(spirv_cross_msl CONFIG REQUIRED)

add_library(dx12
STATIC
    include/glue.h
    include/unknown.h
    include/dxgi.h
    include/d3dcommon.h
    include/d3d12.h
    include/d3d12shader.h
    include/d3dcompiler.h
    include/wrl.h
    src/metal_library.h
    src/metal_helper.h
    src/unknown.cpp
    src/dxgi.cpp
    src/d3d12.cpp
    src/d3dcompiler.cpp
    src/dxgi_object.h
    src/dxgi_object.cpp
    src/dxgi_factory.h
    src/dxgi_factory.cpp
    src/dxgi_device_sub_object.h
    src/dxgi_device_sub_object.cpp
    src/dxgi_swap_chain.h
    src/dxgi_swap_chain.cpp
    src/d3d12_helper.h
    src/d3d12_object.h
    src/d3d12_object.cpp
    src/d3d12_device.h
    src/d3d12_device.cpp
    src/d3d12_device_child.h
    src/d3d12_device_child.cpp
    src/d3d12_pageable.h
    src/d3d12_pageable.cpp
    src/d3d12_command_queue.h
    src/d3d12_command_queue.cpp
    src/d3d12_command_allocator.h
    src/d3d12_command_allocator.cpp
    src/d3d12_command_list.h
    src/d3d12_command_list.cpp
    src/d3d12_graphics_command_list.h
    src/d3d12_graphics_command_list.cpp
    src/d3d12_descriptor_heap.h
    src/d3d12_descriptor_heap.cpp
    src/d3d12_resource.h
    src/d3d12_resource.cpp
    src/d3d_blob.h
    src/d3d_blob.cpp
    src/d3d_compiler.h
    src/d3d_compiler.cpp
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
    fmt::fmt
    glslang::HLSL
    glslang::SPIRV
    glslang::glslang
    glslang::OGLCompiler
    SPIRV-Tools
    spirv-cross-core
    spirv-cross-glsl
    spirv-cross-msl
)

set_target_properties(dx12
PROPERTIES
    CXX_STANDARD 17
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
)

if(BUILD_DEMO)

find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(dx12_demo
    demo/d3dx12.h
    demo/app.h
    demo/app.cpp
    demo/clear_rtv_app.h
    demo/clear_rtv_app.cpp
    demo/main.cpp
)

target_link_libraries(dx12_demo
PRIVATE
    dx12
    spdlog::spdlog
    glfw
)

set_target_properties(dx12_demo
PROPERTIES
    CXX_STANDARD 17
)

endif()
