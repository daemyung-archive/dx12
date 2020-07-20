//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_buffer.h"

#include <cassert>
#include <new>
#include <spdlog/spdlog.h>

#include "d3d12_device.h"
#include "metal_helper.h"

//----------------------------------------------------------------------------------------------------------------------

using namespace std;
using namespace spdlog;

//----------------------------------------------------------------------------------------------------------------------

D3D12Buffer::D3D12Buffer(
    D3D12Device* device,
    const D3D12_HEAP_PROPERTIES* heap_properties,
    D3D12_HEAP_FLAGS heap_flags,
    const D3D12_RESOURCE_DESC* resource_desc)
: D3D12Resource(device, heap_properties, heap_flags, resource_desc)
, buffer_(nil) {
    assert(resource_desc_.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER);
    assert(resource_desc_.Width != 0);
    assert(resource_desc_.Height == 1);

    buffer_ = [device_->GetDevice() newBufferWithLength:resource_desc_.Width
                                                options:ToResourceStorageMode(heap_properties_.Type)];
    if (!buffer_) {
        error("Fail to create a MTLBuffer");
        throw bad_alloc();
    }
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Buffer::Map(
    UINT Subresource,
    _In_opt_  const D3D12_RANGE *pReadRange,
    _Outptr_opt_result_bytebuffer_(_Inexpressible_("Dependent on resource"))  void **ppData) {
    if (heap_properties_.Type != D3D12_HEAP_TYPE_UPLOAD &&
        heap_properties_.Type != D3D12_HEAP_TYPE_READBACK) {
        return E_FAIL;
    }

    *ppData = nullptr;
    *ppData = [buffer_ contents];
    assert(*ppData);

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Buffer::Unmap(
    UINT Subresource,
    _In_opt_  const D3D12_RANGE *pWrittenRange) {
}

//----------------------------------------------------------------------------------------------------------------------

void D3D12Buffer::BindAsVertexBuffer(
    id<MTLRenderCommandEncoder> encoder,
    uint32_t offset,
    uint32_t index) {
    [encoder setVertexBuffer:buffer_
                      offset:offset
                     atIndex:index + 16];
}

//----------------------------------------------------------------------------------------------------------------------

id<MTLBuffer> D3D12Buffer::GetBuffer() const {
    return buffer_;
}

//----------------------------------------------------------------------------------------------------------------------
