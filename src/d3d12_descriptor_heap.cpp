//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_descriptor_heap.h"

#include <cassert>

//----------------------------------------------------------------------------------------------------------------------

D3D12DescriptorHeap::D3D12DescriptorHeap(D3D12Device* device_ptr, const D3D12_DESCRIPTOR_HEAP_DESC* desc_ptr)
: D3D12Pageable(device_ptr), desc_(*desc_ptr) {
    resource_ptrs_.resize(desc_ptr->NumDescriptors);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DescriptorHeap::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return D3D12Pageable::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12DescriptorHeap::AddRef( void) {
    return D3D12Pageable::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12DescriptorHeap::Release( void) {
    return D3D12Pageable::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DescriptorHeap::GetPrivateData(
    _In_  REFGUID guid,
    _Inout_  UINT *pDataSize,
    _Out_writes_bytes_opt_( *pDataSize )  void *pData) {
    return D3D12Pageable::GetPrivateData(guid, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DescriptorHeap::SetPrivateData(
    _In_  REFGUID guid,
    _In_  UINT DataSize,
    _In_reads_bytes_opt_( DataSize )  const void *pData) {
    return D3D12Pageable::SetPrivateData(guid, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DescriptorHeap::SetPrivateDataInterface(
    _In_  REFGUID guid,
    _In_opt_  const IUnknown *pData) {
    return D3D12Pageable::SetPrivateDataInterface(guid, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DescriptorHeap::SetName(
    _In_z_  LPCWSTR Name) {
    return D3D12Pageable::SetName(Name);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DescriptorHeap::GetDevice(
    REFIID riid,
    _COM_Outptr_opt_  void **ppvDevice) {
    return D3D12Pageable::GetDevice(riid, ppvDevice);
}

//----------------------------------------------------------------------------------------------------------------------

D3D12_DESCRIPTOR_HEAP_DESC STDMETHODCALLTYPE D3D12DescriptorHeap::GetDesc( void) {
    return desc_;
}

//----------------------------------------------------------------------------------------------------------------------

D3D12_CPU_DESCRIPTOR_HANDLE STDMETHODCALLTYPE D3D12DescriptorHeap::GetCPUDescriptorHandleForHeapStart( void) {
    return D3D12_CPU_DESCRIPTOR_HANDLE {
        .ptr = reinterpret_cast<SIZE_T>(resource_ptrs_.data())
    };
}

//----------------------------------------------------------------------------------------------------------------------

D3D12_GPU_DESCRIPTOR_HANDLE STDMETHODCALLTYPE D3D12DescriptorHeap::GetGPUDescriptorHandleForHeapStart( void) {
    return D3D12_GPU_DESCRIPTOR_HANDLE {
        .ptr = reinterpret_cast<UINT64>(resource_ptrs_.data())
    };
}

//----------------------------------------------------------------------------------------------------------------------
