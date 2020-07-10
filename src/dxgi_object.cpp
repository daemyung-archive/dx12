//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "dxgi_object.h"

#include <cassert>

//----------------------------------------------------------------------------------------------------------------------

DXGIObject::DXGIObject(DXGIFactory* factory)
: factory_(factory) {
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIObject::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return Unknown::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE DXGIObject::AddRef( void) {
    return Unknown::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE DXGIObject::Release( void) {
    return Unknown::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIObject::SetPrivateData(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [in] */ UINT DataSize,
    /* [annotation][in] */
    _In_reads_bytes_(DataSize)  const void *pData) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIObject::SetPrivateDataInterface(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [annotation][in] */
    _In_opt_  const IUnknown *pUnknown) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIObject::GetPrivateData(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [annotation][out][in] */
    _Inout_  UINT *pDataSize,
    /* [annotation][out] */
    _Out_writes_bytes_(*pDataSize)  void *pData) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIObject::GetParent(
    /* [annotation][in] */
    _In_  REFIID riid,
    /* [annotation][retval][out] */
    _COM_Outptr_  void **ppParent) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------
