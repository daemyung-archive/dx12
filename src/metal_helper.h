//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_METAL_HELPER_H_
#define DX12_METAL_HELPER_H_

#include <stdexcept>

#include "dxgi.h"
#include "metal_library.h"

//----------------------------------------------------------------------------------------------------------------------

inline auto ToWindow(HWND window) {
    return (__bridge NSWindow*)window;
}

//----------------------------------------------------------------------------------------------------------------------

inline auto IsFramebufferOnly(DXGI_USAGE usage) {
    return usage == DXGI_USAGE_RENDER_TARGET_OUTPUT;
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToPixelFormat(DXGI_FORMAT format) {
    switch (format) {
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            return MTLPixelFormatRGBA8Unorm;
        case DXGI_FORMAT_B8G8R8A8_UNORM:
            return MTLPixelFormatBGRA8Unorm;
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
            return MTLPixelFormatDepth24Unorm_Stencil8;
        default:
            throw std::runtime_error("invalid format");
    }
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToViewport(const D3D12_VIEWPORT& viewport) {
    return MTLViewport {
        .originX = viewport.TopLeftX,
        .originY = viewport.TopLeftY,
        .width = viewport.Width,
        .height = viewport.Height,
        .znear = viewport.MinDepth,
        .zfar = viewport.MaxDepth
    };
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToScissorRect(const D3D12_RECT& rect) {
    return MTLScissorRect {
        .height = static_cast<NSUInteger>(rect.left),
        .width = static_cast<NSUInteger>(rect.top),
        .x = static_cast<NSUInteger>(rect.right),
        .y = static_cast<NSUInteger>(rect.bottom)
    };
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToClearColor(const FLOAT color[4]) {
    return MTLClearColorMake(color[0], color[1], color[2], color[3]);
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToTextureType(D3D12_RESOURCE_DIMENSION dimension, bool is_array, bool is_multisample) {
    switch (dimension) {
        case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
            return !is_array ? MTLTextureType1D : MTLTextureType1DArray;
        case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
            if (!is_multisample) {
                return !is_array ? MTLTextureType2D : MTLTextureType2DArray;
            } else {
                return !is_array ? MTLTextureType2DMultisample : MTLTextureType2DMultisampleArray;
            }
        case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
            return MTLTextureType3D;
        default:
            throw std::runtime_error("invalid dimension");
    }
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToResourceStorageMode(D3D12_HEAP_TYPE type) {
    switch (type) {
        case D3D12_HEAP_TYPE_DEFAULT:
            return MTLResourceStorageModePrivate;
        case D3D12_HEAP_TYPE_UPLOAD:
        case D3D12_HEAP_TYPE_READBACK:
            return MTLResourceStorageModeShared;
        default:
            throw std::runtime_error("invalid dimension");
    }
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToTextureUsage(D3D12_RESOURCE_FLAGS flags) {
    MTLTextureUsage usage = MTLTextureUsageShaderRead;

    if (flags & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET ||
        flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL) {
        usage |= MTLTextureUsageRenderTarget;
    }

    if (flags & D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS) {
        usage |= MTLTextureUsageShaderWrite;
    }

    if (flags & D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE) {
        usage &= ~MTLTextureUsageShaderRead;
    }

    return usage;
}

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_METAL_HELPER_H_
