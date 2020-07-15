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
        .x = static_cast<NSUInteger>(rect.left),
        .y = static_cast<NSUInteger>(rect.top),
        .width = static_cast<NSUInteger>(rect.right),
        .height = static_cast<NSUInteger>(rect.bottom)
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

inline auto GetSize(DXGI_FORMAT format) {
    switch (format) {
        case DXGI_FORMAT_R8G8B8A8_UNORM:
        case DXGI_FORMAT_B8G8R8A8_UNORM:
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
            return 4;
        case DXGI_FORMAT_R32G32B32_FLOAT:
            return 12;
        case DXGI_FORMAT_R32G32B32A32_FLOAT:
            return 16;
        default:
            throw std::runtime_error("invalid format");
    }
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToVertexStepFunction(D3D12_INPUT_CLASSIFICATION classification)
{
    switch (classification) {
        case D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA:
            return MTLVertexStepFunctionPerVertex;
        case D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA:
            return MTLVertexStepFunctionPerInstance;
        default:
            throw std::runtime_error("invalid the step rate");
    }
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToVertexFormat(DXGI_FORMAT format)
{
    switch (format) {
        case DXGI_FORMAT_R32G32_FLOAT:
            return MTLVertexFormatFloat2;
        case DXGI_FORMAT_R32G32B32_FLOAT:
            return MTLVertexFormatFloat3;
        case DXGI_FORMAT_R32G32B32A32_FLOAT:
            return MTLVertexFormatFloat4;
        default:
            throw std::runtime_error("invalid the format");
    }
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToBlendFactor(D3D12_BLEND blend)
{
    switch (blend) {
        case D3D12_BLEND_ZERO:
            return MTLBlendFactorZero;
        case D3D12_BLEND_ONE:
            return MTLBlendFactorOne;
        case D3D12_BLEND_SRC_ALPHA:
            return MTLBlendFactorSourceAlpha;
        case D3D12_BLEND_INV_SRC_ALPHA:
            return MTLBlendFactorOneMinusSourceAlpha;
        case D3D12_BLEND_DEST_ALPHA:
            return MTLBlendFactorDestinationAlpha;
        case D3D12_BLEND_INV_DEST_ALPHA:
            return MTLBlendFactorOneMinusDestinationAlpha;
        default:
            throw std::runtime_error("invalid the blend");
    }
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToBlendOperation(D3D12_BLEND_OP op)
{
    switch (op) {
        case D3D12_BLEND_OP_ADD:
            return MTLBlendOperationAdd;
        case D3D12_BLEND_OP_SUBTRACT:
            return MTLBlendOperationSubtract;
        case D3D12_BLEND_OP_REV_SUBTRACT:
            return MTLBlendOperationReverseSubtract;
        case D3D12_BLEND_OP_MIN:
            return MTLBlendOperationMin;
        case D3D12_BLEND_OP_MAX:
            return MTLBlendOperationMax;
        default:
            throw std::runtime_error("invalid the blend op");
    }
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToPrimitiveTopologyClass(D3D12_PRIMITIVE_TOPOLOGY_TYPE type)
{
    switch (type) {
        case D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT:
            return MTLPrimitiveTopologyClassPoint;
        case D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE:
            return MTLPrimitiveTopologyClassLine;
        case D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE:
            return MTLPrimitiveTopologyClassTriangle;
        default:
            throw std::runtime_error("invalid the topology type");
    }
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToPrimitiveType(D3D12_PRIMITIVE_TOPOLOGY topology) {
    switch (topology) {
            case D3D_PRIMITIVE_TOPOLOGY_POINTLIST:
            return MTLPrimitiveTypePoint;
        case D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
            return MTLPrimitiveTypeTriangle;
        case D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
            return MTLPrimitiveTypeTriangleStrip;
       default:
            throw std::runtime_error("invalid the topology");
    }
}

//----------------------------------------------------------------------------------------------------------------------

inline auto ToCullMode(D3D12_CULL_MODE mode) {
    switch (mode) {
        case D3D12_CULL_MODE_NONE:
            return MTLCullModeNone;
        case D3D12_CULL_MODE_FRONT:
            return MTLCullModeFront;
        case D3D12_CULL_MODE_BACK:
            return MTLCullModeBack;
    }
}

#endif // DX12_METAL_HELPER_H_
