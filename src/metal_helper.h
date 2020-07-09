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

inline auto ToPixelFormat(DXGI_FORMAT format) {
    switch (format) {
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            return MTLPixelFormatRGBA8Unorm;
        case DXGI_FORMAT_B8G8R8A8_UNORM:
            return MTLPixelFormatBGRA8Unorm;
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

#endif // DX12_METAL_HELPER_H_
