//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_command_list.h"

#include <cassert>

//----------------------------------------------------------------------------------------------------------------------

D3D12CommandList::D3D12CommandList(D3D12Device* device_ptr)
: D3D12DeviceChild(device_ptr) {
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandList::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return D3D12DeviceChild::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12CommandList::AddRef( void) {
    return D3D12DeviceChild::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12CommandList::Release( void) {
    return D3D12DeviceChild::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandList::GetPrivateData(
    _In_  REFGUID guid,
    _Inout_  UINT *pDataSize,
    _Out_writes_bytes_opt_( *pDataSize )  void *pData) {
    return D3D12DeviceChild::GetPrivateData(guid, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandList::SetPrivateData(
    _In_  REFGUID guid,
    _In_  UINT DataSize,
    _In_reads_bytes_opt_( DataSize )  const void *pData) {
    return D3D12DeviceChild::SetPrivateData(guid, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandList::SetPrivateDataInterface(
    _In_  REFGUID guid,
    _In_opt_  const IUnknown *pData) {
    return D3D12DeviceChild::SetPrivateDataInterface(guid, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandList::SetName(
    _In_z_  LPCWSTR Name) {
    return D3D12DeviceChild::SetName(Name);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandList::GetDevice(
    REFIID riid,
    _COM_Outptr_opt_  void **ppvDevice) {
    return D3D12DeviceChild::GetDevice(riid, ppvDevice);
}

//----------------------------------------------------------------------------------------------------------------------

D3D12_COMMAND_LIST_TYPE STDMETHODCALLTYPE D3D12CommandList::GetType( void) {
    assert(false && "Not implement!!!");
    return D3D12_COMMAND_LIST_TYPE_DIRECT;
}

//----------------------------------------------------------------------------------------------------------------------

D3D12CommandAllocator* D3D12CommandList::GetCommandAllocator() const {
    return command_allocator_ptr_;
}

//----------------------------------------------------------------------------------------------------------------------

void D3D12CommandList::SetCommandAllocator(D3D12CommandAllocator* command_allocator_ptr) {
    command_allocator_ptr_ = command_allocator_ptr;
}

//----------------------------------------------------------------------------------------------------------------------
