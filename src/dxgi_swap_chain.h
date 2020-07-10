//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_DXGI_SWAP_CHAIN_H_
#define DX12_DXGI_SWAP_CHAIN_H_

#include <memory>

#include "dxgi.h"
#include "dxgi_device_sub_object.h"
#include "d3d12_resource.h"
#include "metal_library.h"

//----------------------------------------------------------------------------------------------------------------------

class D3D12CommandQueue;

//----------------------------------------------------------------------------------------------------------------------

class DXGISwapChain : public IDXGISwapChain, public DXGIDeviceSubObject {
public:
    DXGISwapChain( DXGIFactory* factory, D3D12Device* device, D3D12CommandQueue* command_queue,
        const DXGI_SWAP_CHAIN_DESC* desc);

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

    HRESULT STDMETHODCALLTYPE GetDevice(
        /* [annotation][in] */
        _In_  REFIID riid,
        /* [annotation][retval][out] */
        _COM_Outptr_  void **ppDevice) override;

    HRESULT STDMETHODCALLTYPE Present(
        /* [in] */ UINT SyncInterval,
        /* [in] */ UINT Flags) override;

    HRESULT STDMETHODCALLTYPE GetBuffer(
        /* [in] */ UINT Buffer,
        /* [annotation][in] */
        _In_  REFIID riid,
        /* [annotation][out][in] */
        _COM_Outptr_  void **ppSurface) override;

    HRESULT STDMETHODCALLTYPE SetFullscreenState(
        /* [in] */ BOOL Fullscreen,
        /* [annotation][in] */
        _In_opt_  IDXGIOutput *pTarget) override;

    HRESULT STDMETHODCALLTYPE GetFullscreenState(
        /* [annotation][out] */
        _Out_opt_  BOOL *pFullscreen,
        /* [annotation][out] */
        _COM_Outptr_opt_result_maybenull_  IDXGIOutput **ppTarget) override;

    HRESULT STDMETHODCALLTYPE GetDesc(
        /* [annotation][out] */
        _Out_  DXGI_SWAP_CHAIN_DESC *pDesc) override;

    HRESULT STDMETHODCALLTYPE ResizeBuffers(
        /* [in] */ UINT BufferCount,
        /* [in] */ UINT Width,
        /* [in] */ UINT Height,
        /* [in] */ DXGI_FORMAT NewFormat,
        /* [in] */ UINT SwapChainFlags) override;

    HRESULT STDMETHODCALLTYPE ResizeTarget(
        /* [annotation][in] */
        _In_  const DXGI_MODE_DESC *pNewTargetParameters) override;

    HRESULT STDMETHODCALLTYPE GetContainingOutput(
        /* [annotation][out] */
        _COM_Outptr_  IDXGIOutput **ppOutput) override;

    HRESULT STDMETHODCALLTYPE GetFrameStatistics(
        /* [annotation][out] */
        _Out_  DXGI_FRAME_STATISTICS *pStats) override;

    HRESULT STDMETHODCALLTYPE GetLastPresentCount(
        /* [annotation][out] */
        _Out_  UINT *pLastPresentCount) override;

    id<CAMetalDrawable> GetDrawable() const;

private:
    D3D12CommandQueue* command_queue_ = { nullptr };
    DXGI_SWAP_CHAIN_DESC desc_;
    CAMetalLayer* layer_ = { nil };
    mutable id<CAMetalDrawable> drawable_ = { nil };
    std::unique_ptr<D3D12Resource> buffer_;
};

//----------------------------------------------------------------------------------------------------------------------

#endif
