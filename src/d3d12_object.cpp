//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_object.h"

#include <cassert>

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Object::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return Unknown::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12Object::AddRef( void) {
    return Unknown::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12Object::Release( void) {
    return Unknown::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Object::GetPrivateData(
    _In_  REFGUID guid,
    _Inout_  UINT *pDataSize,
    _Out_writes_bytes_opt_( *pDataSize )  void *pData) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Object::SetPrivateData(
    _In_  REFGUID guid,
    _In_  UINT DataSize,
    _In_reads_bytes_opt_( DataSize )  const void *pData) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Object::SetPrivateDataInterface(
    _In_  REFGUID guid,
    _In_opt_  const IUnknown *pData) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Object::SetName(
    _In_z_  LPCWSTR Name) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------
