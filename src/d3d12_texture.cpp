//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_texture.h"

#include <cassert>
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
    const D3D12_RESOURCE_DESC* desc,
    const D3D12_CLEAR_VALUE *clear_value)
: D3D12Resource(device, heap_properties, heap_flags, desc)
, texture_(nil)
, swap_chain_(nullptr) {
    assert(desc_.Dimension != D3D12_RESOURCE_DIMENSION_BUFFER);

    InitTexture();
}

//----------------------------------------------------------------------------------------------------------------------

D3D12Texture::D3D12Texture(
    D3D12Device* device,
    DXGISwapChain* swap_chain,
    const D3D12_HEAP_PROPERTIES* heap_properties,
    D3D12_HEAP_FLAGS heap_flags,
    const D3D12_RESOURCE_DESC* desc)
: D3D12Resource(device, heap_properties, heap_flags, desc)
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

void D3D12Texture::InitTexture() {
    auto descriptor = [MTLTextureDescriptor new];
    assert(descriptor && "Fail to create MTLTextureDescriptor");

    descriptor.textureType = ToTextureType(
        desc_.Dimension,
        desc_.DepthOrArraySize,
        desc_.SampleDesc.Count != 1);
    descriptor.pixelFormat = ToPixelFormat(desc_.Format);
    descriptor.width = desc_.Width;
    descriptor.height = desc_.Height;

    if (desc_.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE3D) {
        descriptor.depth = desc_.DepthOrArraySize;
        descriptor.arrayLength = 1;
    } else {
        descriptor.depth = 1;
        descriptor.arrayLength = desc_.DepthOrArraySize;
    }

    descriptor.mipmapLevelCount = desc_.MipLevels;
    descriptor.sampleCount = desc_.SampleDesc.Count;

    if (desc_.Layout == D3D12_TEXTURE_LAYOUT_UNKNOWN) {
        descriptor.allowGPUOptimizedContents = YES;
    } else {
        descriptor.allowGPUOptimizedContents = NO;
    }

    descriptor.resourceOptions = ToResourceOptions(heap_properties_.Type);
    descriptor.usage = ToTextureUsage(desc_.Flags);

    texture_ = [device_->GetDevice() newTextureWithDescriptor:descriptor];
    assert(texture_ && "Fail to create MTLTexture");
}

//----------------------------------------------------------------------------------------------------------------------
