//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_resource.h"

#include <cassert>

#include "dxgi_swap_chain.h"
#include "d3d12_device.h"
#include "metal_helper.h"

//----------------------------------------------------------------------------------------------------------------------

D3D12Resource::D3D12Resource(D3D12Device* device, const D3D12_HEAP_PROPERTIES* heap_properties,
    D3D12_HEAP_FLAGS heap_flags, const D3D12_RESOURCE_DESC* desc, const D3D12_CLEAR_VALUE *clear_value)
: D3D12Pageable(device), heap_properties_(*heap_properties), heap_flags_(heap_flags), desc_(*desc) {
    if (desc_.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER) {
        buffer_ = [device_->GetDevice() newBufferWithLength:desc_.Width
                                                    options:ToResourceStorageMode(heap_properties_.Type)];
        assert(buffer_);
    }
    else {
        auto descriptor = [MTLTextureDescriptor new];
        descriptor.textureType = ToTextureType(desc_.Dimension,
            desc_.DepthOrArraySize, desc_.SampleDesc.Count != 1);
        descriptor.pixelFormat = ToPixelFormat(desc_.Format);
        descriptor.width = desc_.Width;
        descriptor.height = desc_.Height;
        descriptor.depth = (desc_.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE3D)
            ? desc_.DepthOrArraySize : 1;
        descriptor.mipmapLevelCount = desc_.MipLevels;
        descriptor.sampleCount = desc_.SampleDesc.Count;
        descriptor.arrayLength = (desc_.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE3D)
            ? desc_.DepthOrArraySize : 1;
        descriptor.allowGPUOptimizedContents = (desc_.Layout == D3D12_TEXTURE_LAYOUT_UNKNOWN)
            ? YES : NO;
        descriptor.resourceOptions = ToResourceStorageMode(heap_properties_.Type);
        descriptor.usage = ToTextureUsage(desc_.Flags);

        texture_ = [device_->GetDevice() newTextureWithDescriptor:descriptor];
        assert(texture_);

        if (clear_value) {
            
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------

D3D12Resource::D3D12Resource(D3D12Device* device, DXGISwapChain* swap_chain)
: D3D12Pageable(device), swap_chain_ptr_(swap_chain) {
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Resource::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return D3D12Pageable::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12Resource::AddRef( void) {
    return D3D12Pageable::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12Resource::Release( void) {
    return D3D12Pageable::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Resource::GetPrivateData(
    _In_  REFGUID guid,
    _Inout_  UINT *pDataSize,
    _Out_writes_bytes_opt_( *pDataSize )  void *pData) {
    return D3D12Pageable::GetPrivateData(guid, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Resource::SetPrivateData(
    _In_  REFGUID guid,
    _In_  UINT DataSize,
    _In_reads_bytes_opt_( DataSize )  const void *pData) {
    return D3D12Pageable::SetPrivateData(guid, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Resource::SetPrivateDataInterface(
    _In_  REFGUID guid,
    _In_opt_  const IUnknown *pData) {
    return D3D12Pageable::SetPrivateDataInterface(guid, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Resource::SetName(
    _In_z_  LPCWSTR Name) {
    return D3D12Pageable::SetName(Name);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Resource::GetDevice(
    REFIID riid,
    _COM_Outptr_opt_  void **ppvDevice) {
    return D3D12Pageable::GetDevice(riid, ppvDevice);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Resource::Map(
    UINT Subresource,
    _In_opt_  const D3D12_RANGE *pReadRange,
    _Outptr_opt_result_bytebuffer_(_Inexpressible_("Dependent on resource"))  void **ppData) {
    *ppData = [buffer_ contents];

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Resource::Unmap(
    UINT Subresource,
    _In_opt_  const D3D12_RANGE *pWrittenRange) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

D3D12_RESOURCE_DESC STDMETHODCALLTYPE D3D12Resource::GetDesc( void) {
    return desc_;
}

//----------------------------------------------------------------------------------------------------------------------

D3D12_GPU_VIRTUAL_ADDRESS STDMETHODCALLTYPE D3D12Resource::GetGPUVirtualAddress( void) {
    return reinterpret_cast<D3D12_GPU_VIRTUAL_ADDRESS>(this);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Resource::WriteToSubresource(
    UINT DstSubresource,
    _In_opt_  const D3D12_BOX *pDstBox,
    _In_  const void *pSrcData,
    UINT SrcRowPitch,
    UINT SrcDepthPitch) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Resource::ReadFromSubresource(
    _Out_  void *pDstData,
    UINT DstRowPitch,
    UINT DstDepthPitch,
    UINT SrcSubresource,
    _In_opt_  const D3D12_BOX *pSrcBox) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Resource::GetHeapProperties(
    _Out_opt_  D3D12_HEAP_PROPERTIES *pHeapProperties,
    _Out_opt_  D3D12_HEAP_FLAGS *pHeapFlags) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

id<MTLBuffer> D3D12Resource::GetBuffer() const {
    return buffer_;
}

//----------------------------------------------------------------------------------------------------------------------

id<MTLTexture> D3D12Resource::GetTexture() const {
    return swap_chain_ptr_ ? swap_chain_ptr_->GetDrawable().texture : texture_;
}

//----------------------------------------------------------------------------------------------------------------------
