//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_device_child.h"

//----------------------------------------------------------------------------------------------------------------------

D3D12DeviceChild::D3D12DeviceChild(D3D12Device* device_ptr)
: device_ptr_(device_ptr) {
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DeviceChild::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return D3D12Object::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12DeviceChild::AddRef( void) {
    return D3D12Object::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12DeviceChild::Release( void) {
    return D3D12Object::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DeviceChild::GetPrivateData(
    _In_  REFGUID guid,
    _Inout_  UINT *pDataSize,
    _Out_writes_bytes_opt_( *pDataSize )  void *pData) {
    return D3D12Object::GetPrivateData(guid, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DeviceChild::SetPrivateData(
    _In_  REFGUID guid,
    _In_  UINT DataSize,
    _In_reads_bytes_opt_( DataSize )  const void *pData) {
    return D3D12Object::SetPrivateData(guid, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DeviceChild::SetPrivateDataInterface(
    _In_  REFGUID guid,
    _In_opt_  const IUnknown *pData) {
    return D3D12Object::SetPrivateDataInterface(guid, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DeviceChild::SetName(
    _In_z_  LPCWSTR Name) {
    return D3D12Object::SetName(Name);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12DeviceChild::GetDevice(
    REFIID riid,
    _COM_Outptr_opt_  void **ppvDevice) {
    *ppvDevice = device_ptr_;
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------
