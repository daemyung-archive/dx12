//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "dxgi_swap_chain.h"

#include <cassert>

#include "d3d12_device.h"
#include "d3d12_command_queue.h"
#include "metal_helper.h"

//----------------------------------------------------------------------------------------------------------------------

DXGISwapChain::DXGISwapChain(DXGIFactory* factory, D3D12Device* device, D3D12CommandQueue* command_queue,
    const DXGI_SWAP_CHAIN_DESC* desc)
: DXGIDeviceSubObject(factory, device), command_queue_(command_queue), desc_(*desc) {
    layer_ = [CAMetalLayer layer];
    assert(layer_);

    layer_.device = device_->GetDevice();
    layer_.pixelFormat = ToPixelFormat(desc_.BufferDesc.Format);
    layer_.framebufferOnly = IsFramebufferOnly(desc_.BufferUsage);
    layer_.maximumDrawableCount = desc_.BufferCount;
    layer_.drawableSize = CGSizeMake(desc_.BufferDesc.Width, desc_.BufferDesc.Height);

    [[ToWindow(desc_.OutputWindow) contentView] setLayer:layer_];

    buffer_ = std::make_unique<D3D12Resource>(device_, this);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return DXGIDeviceSubObject::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE DXGISwapChain::AddRef( void) {
    return DXGIDeviceSubObject::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE DXGISwapChain::Release( void) {
    return DXGIDeviceSubObject::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::SetPrivateData(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [in] */ UINT DataSize,
    /* [annotation][in] */
    _In_reads_bytes_(DataSize)  const void *pData) {
    return DXGIDeviceSubObject::SetPrivateData(Name, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::SetPrivateDataInterface(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [annotation][in] */
    _In_opt_  const IUnknown *pUnknown) {
    return DXGIDeviceSubObject::SetPrivateDataInterface(Name, pUnknown);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::GetPrivateData(
    /* [annotation][in] */
    _In_  REFGUID Name,
    /* [annotation][out][in] */
    _Inout_  UINT *pDataSize,
    /* [annotation][out] */
    _Out_writes_bytes_(*pDataSize)  void *pData) {
    return DXGIDeviceSubObject::GetPrivateData(Name, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::GetParent(
    /* [annotation][in] */
    _In_  REFIID riid,
    /* [annotation][retval][out] */
    _COM_Outptr_  void **ppParent) {
    return DXGIDeviceSubObject::GetParent(riid, ppParent);
};

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::GetDevice(
    /* [annotation][in] */
    _In_  REFIID riid,
    /* [annotation][retval][out] */
    _COM_Outptr_  void **ppDevice) {
    return DXGIDeviceSubObject::GetDevice(riid, ppDevice);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::Present(
    /* [in] */ UINT SyncInterval,
    /* [in] */ UINT Flags) {
    auto command_buffer = [command_queue_->GetCommandQueue() commandBuffer];
    if (!command_buffer) {
        return DXGI_ERROR_DEVICE_REMOVED;
    }

    [command_buffer presentDrawable:drawable_];
    [command_buffer commit];
    drawable_ = nil;

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::GetBuffer(
    /* [in] */ UINT Buffer,
    /* [annotation][in] */
    _In_  REFIID riid,
    /* [annotation][out][in] */
    _COM_Outptr_  void **ppSurface) {
    if (!ppSurface) {
        return DXGI_ERROR_INVALID_CALL;
    }

    *ppSurface = buffer_.get();

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::SetFullscreenState(
    /* [in] */ BOOL Fullscreen,
    /* [annotation][in] */
    _In_opt_  IDXGIOutput *pTarget) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::GetFullscreenState(
    /* [annotation][out] */
    _Out_opt_  BOOL *pFullscreen,
    /* [annotation][out] */
    _COM_Outptr_opt_result_maybenull_  IDXGIOutput **ppTarget) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::GetDesc(
    /* [annotation][out] */
    _Out_  DXGI_SWAP_CHAIN_DESC *pDesc) {
    if (!pDesc) {
        return DXGI_ERROR_INVALID_CALL;
    }

    *pDesc = desc_;

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::ResizeBuffers(
    /* [in] */ UINT BufferCount,
    /* [in] */ UINT Width,
    /* [in] */ UINT Height,
    /* [in] */ DXGI_FORMAT NewFormat,
    /* [in] */ UINT SwapChainFlags) {
    if (desc_.BufferCount != BufferCount) {
        layer_.maximumDrawableCount = BufferCount;

        desc_.BufferCount = BufferCount;
    }

    if (desc_.BufferDesc.Width != Width || desc_.BufferDesc.Height != Height) {
        layer_.drawableSize = CGSizeMake(Width, Height);

        desc_.BufferDesc.Width = Width;
        desc_.BufferDesc.Height = Height;
    }

    if (desc_.BufferDesc.Format != NewFormat) {
        layer_.pixelFormat = ToPixelFormat(NewFormat);

        desc_.BufferDesc.Format = NewFormat;
    }

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::ResizeTarget(
    /* [annotation][in] */
    _In_  const DXGI_MODE_DESC *pNewTargetParameters) {
    if (desc_.BufferDesc.Width != pNewTargetParameters->Width ||
        desc_.BufferDesc.Height != pNewTargetParameters->Height) {
        layer_.drawableSize = CGSizeMake(pNewTargetParameters->Width, pNewTargetParameters->Height);

        desc_.BufferDesc.Width = pNewTargetParameters->Width;
        desc_.BufferDesc.Height = pNewTargetParameters->Height;
    }

    if (desc_.BufferDesc.Format != pNewTargetParameters->Format) {
        layer_.pixelFormat = ToPixelFormat(desc_.BufferDesc.Format);

        desc_.BufferDesc.Format = pNewTargetParameters->Format;
    }

    desc_.BufferDesc.RefreshRate = pNewTargetParameters->RefreshRate;
    desc_.BufferDesc.ScanlineOrdering = pNewTargetParameters->ScanlineOrdering;
    desc_.BufferDesc.Scaling = pNewTargetParameters->Scaling;

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::GetContainingOutput(
    /* [annotation][out] */
    _COM_Outptr_  IDXGIOutput **ppOutput) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::GetFrameStatistics(
    /* [annotation][out] */
    _Out_  DXGI_FRAME_STATISTICS *pStats) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::GetLastPresentCount(
    /* [annotation][out] */
    _Out_  UINT *pLastPresentCount) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

id<CAMetalDrawable> DXGISwapChain::GetDrawable() const {
    if (!drawable_) {
        drawable_ = [layer_ nextDrawable];
    }

    return drawable_;
}

//----------------------------------------------------------------------------------------------------------------------
