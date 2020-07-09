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

DXGISwapChain::DXGISwapChain(
    DXGIFactory* factory_ptr,
    D3D12CommandQueue* command_queue_ptr,
    const DXGI_SWAP_CHAIN_DESC* desc_ptr)
: DXGIDeviceSubObject(factory_ptr), command_queue_ptr_(command_queue_ptr) {
    D3D12Device* device_ptr;
    command_queue_ptr_->GetDevice(IID_PPV_ARGS(&device_ptr));
    assert(device_ptr);

    layer_ = [CAMetalLayer layer];
    layer_.device = device_ptr->GetDevice();
    layer_.pixelFormat = ToPixelFormat(desc_ptr->BufferDesc.Format);
    layer_.framebufferOnly = NO;
    layer_.maximumDrawableCount = desc_ptr->BufferCount;
    layer_.drawableSize = CGSizeMake(desc_ptr->BufferDesc.Width, desc_ptr->BufferDesc.Height);

    [[(__bridge NSWindow*)desc_ptr->OutputWindow contentView] setLayer:layer_];

    for (auto i = 0; i != desc_ptr->BufferCount; ++i) {
        resource_ptrs_.push_back(std::make_unique<D3D12Resource>(device_ptr, this));
    }
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
    assert(false && "Not implement!!!");
    return S_OK;
};

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::GetDevice(
    /* [annotation][in] */
    _In_  REFIID riid,
    /* [annotation][retval][out] */
    _COM_Outptr_  void **ppDevice) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::Present(
    /* [in] */ UINT SyncInterval,
    /* [in] */ UINT Flags) {
    auto command_queue = command_queue_ptr_->GetCommandQueue();
    auto command_buffer = [command_queue commandBuffer];

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
    *ppSurface = resource_ptrs_[Buffer].get();

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
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::ResizeBuffers(
    /* [in] */ UINT BufferCount,
    /* [in] */ UINT Width,
    /* [in] */ UINT Height,
    /* [in] */ DXGI_FORMAT NewFormat,
    /* [in] */ UINT SwapChainFlags) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE DXGISwapChain::ResizeTarget(
    /* [annotation][in] */
    _In_  const DXGI_MODE_DESC *pNewTargetParameters) {
    assert(false && "Not implement!!!");
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
