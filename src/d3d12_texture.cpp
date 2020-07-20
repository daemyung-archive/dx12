//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_texture.h"

#include <cassert>
#include <new>
#include <spdlog/spdlog.h>

#include "dxgi_swap_chain.h"
#include "d3d12_device.h"
#include "metal_helper.h"

//----------------------------------------------------------------------------------------------------------------------

using namespace std;
using namespace spdlog;

//----------------------------------------------------------------------------------------------------------------------

D3D12Texture::D3D12Texture(
    D3D12Device* device,
    const D3D12_HEAP_PROPERTIES* heap_properties,
    D3D12_HEAP_FLAGS heap_flags,
    const D3D12_RESOURCE_DESC* resource_desc,
    const D3D12_CLEAR_VALUE *clear_value)
: D3D12Resource(device, heap_properties, heap_flags, resource_desc)
, texture_(nil)
, swap_chain_(nullptr) {
    assert(resource_desc_.Dimension != D3D12_RESOURCE_DIMENSION_BUFFER);

    auto descriptor = [MTLTextureDescriptor new];
    if (!descriptor) {
        error("Fail to create a MTLTextureDescriptor");
        return bad_alloc();
    }

    descriptor.textureType = ToTextureType(resource_desc_.Dimension,
        resource_desc_.DepthOrArraySize, resource_desc_.SampleDesc.Count != 1);
    descriptor.pixelFormat = ToPixelFormat(resource_desc_.Format);
    descriptor.width = resource_desc_.Width;
    descriptor.height = resource_desc_.Height;
    descriptor.depth = (resource_desc_.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE3D)
        ? resource_desc_.DepthOrArraySize : 1;
    descriptor.mipmapLevelCount = resource_desc_.MipLevels;
    descriptor.sampleCount = resource_desc_.SampleDesc.Count;
    descriptor.arrayLength = (resource_desc_.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE3D)
        ? resource_desc_.DepthOrArraySize : 1;
    descriptor.allowGPUOptimizedContents = (resource_desc_.Layout == D3D12_TEXTURE_LAYOUT_UNKNOWN)
        ? YES : NO;
    descriptor.resourceOptions = ToResourceStorageMode(heap_properties_.Type);
    descriptor.usage = ToTextureUsage(resource_desc_.Flags);

    texture_ = [device_->GetDevice() newTextureWithDescriptor:descriptor];
    if (!texture_) {
        error("Fail to create a MTLTexture");
        return bad_alloc();
    }
}

//----------------------------------------------------------------------------------------------------------------------

D3D12Texture::D3D12Texture(
    D3D12Device* device,
    DXGISwapChain* swap_chain,
    const D3D12_HEAP_PROPERTIES* heap_properties,
    D3D12_HEAP_FLAGS heap_flags,
    const D3D12_RESOURCE_DESC* resource_desc)
: D3D12Resource(device, heap_properties, heap_flags, resource_desc)
, texture_(nil)
, swap_chain_(swap_chain) {
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Texture::Map(
    UINT Subresource,
    _In_opt_  const D3D12_RANGE *pReadRange,
    _Outptr_opt_result_bytebuffer_(_Inexpressible_("Dependent on resource"))  void **ppData) {
    return E_FAIL;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Texture::Unmap(
    UINT Subresource,
    _In_opt_  const D3D12_RANGE *pWrittenRange) {
}

//----------------------------------------------------------------------------------------------------------------------

bool D3D12Texture::isPresentable() const {
    return swap_chain_;
}

//----------------------------------------------------------------------------------------------------------------------

id<MTLTexture> D3D12Texture::GetTexture() const {
    if (isPresentable()) {
        return swap_chain_->GetDrawable().texture;
    } else {
        return texture_;
    }
}

//----------------------------------------------------------------------------------------------------------------------
