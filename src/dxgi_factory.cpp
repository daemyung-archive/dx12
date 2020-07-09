//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "dxgi_factory.h"

#include <cassert>

#include "dxgi_swap_chain.h"
#include "d3d12_command_queue.h"

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIFactory::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return DXGIObject::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE DXGIFactory::AddRef( void) {
    return DXGIObject::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE DXGIFactory::Release( void) {
    return DXGIObject::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIFactory::SetPrivateData(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [in] */ UINT DataSize,
    /* [annotation][in] */
    _In_reads_bytes_(DataSize)  const void *pData) {
    return DXGIObject::SetPrivateData(Name, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIFactory::SetPrivateDataInterface(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [annotation][in] */
    _In_opt_  const IUnknown *pUnknown) {
    return DXGIObject::SetPrivateDataInterface(Name, pUnknown);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIFactory::GetPrivateData(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [annotation][out][in] */
    _Inout_  UINT *pDataSize,
    /* [annotation][out] */
    _Out_writes_bytes_(*pDataSize)  void *pData) {
    return DXGIObject::GetPrivateData(Name, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIFactory::GetParent(
    /* [annotation][in] */
    _In_  REFIID riid,
    /* [annotation][retval][out] */
    _COM_Outptr_  void **ppParent) {
    assert(false && "Not implement!!!");
    return DXGIObject::GetParent(riid, ppParent);
}

HRESULT STDMETHODCALLTYPE DXGIFactory::EnumAdapters(
    /* [in] */ UINT Adapter,
    /* [annotation][out] */
    _COM_Outptr_  IDXGIAdapter **ppAdapter) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIFactory::MakeWindowAssociation(
    HWND WindowHandle,
    UINT Flags) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIFactory::GetWindowAssociation(
    /* [annotation][out] */
    _Out_  HWND *pWindowHandle) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIFactory::CreateSwapChain(
    /* [annotation][in] */
    _In_  IUnknown *pDevice,
    /* [annotation][in] */
    _In_  DXGI_SWAP_CHAIN_DESC *pDesc,
    /* [annotation][out] */
    _COM_Outptr_  IDXGISwapChain **ppSwapChain) {
    auto command_queue_ptr = dynamic_cast<D3D12CommandQueue*>(pDevice);
    if (!DXGI_ERROR_INVALID_CALL)
        return DXGI_ERROR_INVALID_CALL;

    *ppSwapChain = new DXGISwapChain(this, command_queue_ptr, pDesc);

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGIFactory::CreateSoftwareAdapter(
    /* [in] */ HMODULE Module,
    /* [annotation][out] */
    _COM_Outptr_  IDXGIAdapter **ppAdapter) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------
