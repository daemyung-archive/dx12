//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_D3D12_TEXTURE_H_
#define DX12_D3D12_TEXTURE_H_

#include "d3d12_resource.h"
#include "metal_library.h"

//----------------------------------------------------------------------------------------------------------------------

class DXGISwapChain;

//----------------------------------------------------------------------------------------------------------------------

class D3D12Texture final : public D3D12Resource {
public:
    D3D12Texture(
        D3D12Device* device,
        const D3D12_HEAP_PROPERTIES* heap_properties,
        D3D12_HEAP_FLAGS heap_flags,
        const D3D12_RESOURCE_DESC* resource_desc,
        const D3D12_CLEAR_VALUE *clear_value);

    D3D12Texture(
        D3D12Device* device,
        DXGISwapChain* swap_chain,
        const D3D12_HEAP_PROPERTIES* heap_properties,
        D3D12_HEAP_FLAGS heap_flags,
        const D3D12_RESOURCE_DESC* resource_desc);

    HRESULT STDMETHODCALLTYPE Map(
        UINT Subresource,
        _In_opt_  const D3D12_RANGE *pReadRange,
        _Outptr_opt_result_bytebuffer_(_Inexpressible_("Dependent on resource"))  void **ppData) override;

    void STDMETHODCALLTYPE Unmap(
        UINT Subresource,
        _In_opt_  const D3D12_RANGE *pWrittenRange) override;

    bool isPresentable() const;

    id<MTLTexture> GetTexture() const;

private:
    id<MTLTexture> texture_;
    DXGISwapChain* swap_chain_;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_D3D12_TEXTURE_H_
