//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_pageable.h"

#include <cassert>

//----------------------------------------------------------------------------------------------------------------------

D3D12Pageable::D3D12Pageable(D3D12Device* device_ptr)
: D3D12DeviceChild(device_ptr) {
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Pageable::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return D3D12DeviceChild::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12Pageable::AddRef( void) {
    return D3D12DeviceChild::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12Pageable::Release( void) {
    return D3D12DeviceChild::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Pageable::GetPrivateData(
    _In_  REFGUID guid,
    _Inout_  UINT *pDataSize,
    _Out_writes_bytes_opt_( *pDataSize )  void *pData) {
    return D3D12DeviceChild::GetPrivateData(guid, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Pageable::SetPrivateData(
    _In_  REFGUID guid,
    _In_  UINT DataSize,
    _In_reads_bytes_opt_( DataSize )  const void *pData) {
    return D3D12DeviceChild::SetPrivateData(guid, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Pageable::SetPrivateDataInterface(
    _In_  REFGUID guid,
    _In_opt_  const IUnknown *pData) {
    return D3D12DeviceChild::SetPrivateDataInterface(guid, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Pageable::SetName(
    _In_z_  LPCWSTR Name) {
    return D3D12DeviceChild::SetName(Name);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Pageable::GetDevice(
    REFIID riid,
    _COM_Outptr_opt_  void **ppvDevice) {
    return D3D12DeviceChild::GetDevice(riid, ppvDevice);
}

//----------------------------------------------------------------------------------------------------------------------
