//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_DXGI_FACTORY_H_
#define DX12_DXGI_FACTORY_H_

#include "dxgi_object.h"

//----------------------------------------------------------------------------------------------------------------------

class DXGIFactory : public IDXGIFactory, public DXGIObject {
    HRESULT STDMETHODCALLTYPE QueryInterface(
        REFIID riid,
        void **ppvObject) override;

    ULONG STDMETHODCALLTYPE AddRef( void) override;

    ULONG STDMETHODCALLTYPE Release( void) override;

    HRESULT STDMETHODCALLTYPE SetPrivateData(
        /* [annotation][in] */
        _In_  REFGUID Name,
        /* [in] */ UINT DataSize,
        /* [annotation][in] */
        _In_reads_bytes_(DataSize)  const void *pData) override;

    HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(
        /* [annotation][in] */
        _In_  REFGUID Name,
        /* [annotation][in] */
        _In_opt_  const IUnknown *pUnknown) override;

    HRESULT STDMETHODCALLTYPE GetPrivateData(
        /* [annotation][in] */
        _In_  REFGUID Name,
        /* [annotation][out][in] */
        _Inout_  UINT *pDataSize,
        /* [annotation][out] */
        _Out_writes_bytes_(*pDataSize)  void *pData) override;

    HRESULT STDMETHODCALLTYPE GetParent(
        /* [annotation][in] */
        _In_  REFIID riid,
        /* [annotation][retval][out] */
        _COM_Outptr_  void **ppParent) override;

    HRESULT STDMETHODCALLTYPE EnumAdapters(
        /* [in] */ UINT Adapter,
        /* [annotation][out] */
        _COM_Outptr_  IDXGIAdapter **ppAdapter) override;

    HRESULT STDMETHODCALLTYPE MakeWindowAssociation(
        HWND WindowHandle,
        UINT Flags) override;

    HRESULT STDMETHODCALLTYPE GetWindowAssociation(
        /* [annotation][out] */
        _Out_  HWND *pWindowHandle) override;

    HRESULT STDMETHODCALLTYPE CreateSwapChain(
        /* [annotation][in] */
        _In_  IUnknown *pDevice,
        /* [annotation][in] */
        _In_  DXGI_SWAP_CHAIN_DESC *pDesc,
        /* [annotation][out] */
        _COM_Outptr_  IDXGISwapChain **ppSwapChain) override;

    HRESULT STDMETHODCALLTYPE CreateSoftwareAdapter(
        /* [in] */ HMODULE Module,
        /* [annotation][out] */
        _COM_Outptr_  IDXGIAdapter **ppAdapter) override;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_DXGI_FACTORY_H_
