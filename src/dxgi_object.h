//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_DXGI_OBJECT_H_
#define DX12_DXGI_OBJECT_H_

#include "dxgi.h"
#include "unknown.h"

//----------------------------------------------------------------------------------------------------------------------

class DXGIFactory;

//----------------------------------------------------------------------------------------------------------------------

class DXGIObject : public IDXGIObject, public Unknown {
public:
    explicit DXGIObject(DXGIFactory* factory);

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

protected:
    DXGIFactory* factory_ = { nullptr };
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_DXGI_OBJECT_H_
