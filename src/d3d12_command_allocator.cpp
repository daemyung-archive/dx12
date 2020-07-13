//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_command_allocator.h"

#include <cassert>

#include "d3d12_device.h"

//----------------------------------------------------------------------------------------------------------------------

D3D12CommandAllocator::D3D12CommandAllocator(D3D12Device* device_ptr)
: D3D12Pageable(device_ptr) {
    auto command_queue = device_->GetCommandQueue();
    assert(command_queue);

    command_buffer_ = [command_queue commandBuffer];
    assert(command_buffer_);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandAllocator::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return D3D12Pageable::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12CommandAllocator::AddRef( void) {
    return D3D12Pageable::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12CommandAllocator::Release( void) {
    return D3D12Pageable::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandAllocator::GetPrivateData(
    _In_  REFGUID guid,
    _Inout_  UINT *pDataSize,
    _Out_writes_bytes_opt_( *pDataSize )  void *pData) {
    return D3D12Pageable::GetPrivateData(guid, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandAllocator::SetPrivateData(
    _In_  REFGUID guid,
    _In_  UINT DataSize,
    _In_reads_bytes_opt_( DataSize )  const void *pData) {
    return D3D12Pageable::SetPrivateData(guid, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandAllocator::SetPrivateDataInterface(
    _In_  REFGUID guid,
    _In_opt_  const IUnknown *pData) {
    return D3D12Pageable::SetPrivateDataInterface(guid, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandAllocator::SetName(
    _In_z_  LPCWSTR Name) {
    return D3D12Pageable::SetName(Name);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandAllocator::GetDevice(
    REFIID riid,
    _COM_Outptr_opt_  void **ppvDevice) {
    return D3D12Pageable::GetDevice(riid, ppvDevice);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandAllocator::Reset( void) {
    if (!command_buffer_)
        return E_FAIL;

    auto command_queue = device_->GetCommandQueue();
    assert(command_queue);

    command_buffer_ = [command_queue commandBuffer];

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

id<MTLCommandBuffer> D3D12CommandAllocator::GetCommandBuffer() const {
    return command_buffer_;
}

//----------------------------------------------------------------------------------------------------------------------
