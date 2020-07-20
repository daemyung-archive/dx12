//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_D3D12_BUFFER_H_
#define DX12_D3D12_BUFFER_H_

#include "d3d12_resource.h"
#include "metal_library.h"

//----------------------------------------------------------------------------------------------------------------------

class D3D12Buffer final : public D3D12Resource {
public:
    D3D12Buffer(
        D3D12Device* device,
        const D3D12_HEAP_PROPERTIES* heap_properties,
        D3D12_HEAP_FLAGS heap_flags,
        const D3D12_RESOURCE_DESC* desc);

    HRESULT STDMETHODCALLTYPE Map(
        UINT Subresource,
        _In_opt_  const D3D12_RANGE *pReadRange,
        _Outptr_opt_result_bytebuffer_(_Inexpressible_("Dependent on resource"))  void **ppData) override;

    void STDMETHODCALLTYPE Unmap(
        UINT Subresource,
        _In_opt_  const D3D12_RANGE *pWrittenRange) override;

    void BindAsVertexBuffer(
        id<MTLRenderCommandEncoder> encoder,
        uint32_t offset,
        uint32_t index);

    id<MTLBuffer> GetBuffer() const;

private:
    void InitBuffer();
    
private:
    id<MTLBuffer> buffer_;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_D3D12_BUFFER_H_
