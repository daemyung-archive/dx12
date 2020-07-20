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

D3D12Resource::D3D12Resource(
    D3D12Device* device,
    const D3D12_HEAP_PROPERTIES* heap_properties,
    D3D12_HEAP_FLAGS heap_flags,
    const D3D12_RESOURCE_DESC* resource_desc)
: D3D12Pageable(device),
  heap_properties_(*heap_properties),
  heap_flags_(heap_flags),
  resource_desc_(*resource_desc) {
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

D3D12_RESOURCE_DESC STDMETHODCALLTYPE D3D12Resource::GetDesc( void) {
    return resource_desc_;
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
