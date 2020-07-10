//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "dxgi_device_sub_object.h"

#include <cassert>

//----------------------------------------------------------------------------------------------------------------------

DXGIDeviceSubObject::DXGIDeviceSubObject(DXGIFactory* factory, D3D12Device* device)
: DXGIObject(factory), device_(device) {
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIDeviceSubObject::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return DXGIObject::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE DXGIDeviceSubObject::AddRef( void) {
    return DXGIObject::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE DXGIDeviceSubObject::Release( void) {
    return DXGIObject::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIDeviceSubObject::SetPrivateData(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [in] */ UINT DataSize,
    /* [annotation][in] */
    _In_reads_bytes_(DataSize)  const void *pData) {
    return DXGIObject::SetPrivateData(Name, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIDeviceSubObject::SetPrivateDataInterface(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [annotation][in] */
    _In_opt_  const IUnknown *pUnknown) {
    return DXGIObject::SetPrivateDataInterface(Name, pUnknown);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIDeviceSubObject::GetPrivateData(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [annotation][out][in] */
    _Inout_  UINT *pDataSize,
    /* [annotation][out] */
    _Out_writes_bytes_(*pDataSize)  void *pData) {
    return DXGIObject::GetPrivateData(Name, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIDeviceSubObject::GetParent(
    /* [annotation][in] */
    _In_  REFIID riid,
    /* [annotation][retval][out] */
    _COM_Outptr_  void **ppParent) {
    return DXGIObject::GetParent(riid, ppParent);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIDeviceSubObject::GetDevice(
    /* [annotation][in] */
    _In_  REFIID riid,
    /* [annotation][retval][out] */
    _COM_Outptr_  void **ppDevice) {
    *ppDevice = static_cast<void*>(device_);
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------
