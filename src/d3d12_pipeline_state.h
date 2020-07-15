//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_D3D12_PIPELINE_STATE_H_
#define DX12_D3D12_PIPELINE_STATE_H_

#include "d3d12_pageable.h"
#include "metal_library.h"

//----------------------------------------------------------------------------------------------------------------------

class D3D12PipelineState : public ID3D12PipelineState, public D3D12Pageable {
public:
    D3D12PipelineState(D3D12Device* device, const D3D12_GRAPHICS_PIPELINE_STATE_DESC* desc);

    HRESULT STDMETHODCALLTYPE QueryInterface(
        REFIID riid,
        void **ppvObject) override;

    ULONG STDMETHODCALLTYPE AddRef( void) override;

    ULONG STDMETHODCALLTYPE Release( void) override;

    HRESULT STDMETHODCALLTYPE GetPrivateData(
        _In_  REFGUID guid,
        _Inout_  UINT *pDataSize,
        _Out_writes_bytes_opt_( *pDataSize )  void *pData) override;

    HRESULT STDMETHODCALLTYPE SetPrivateData(
        _In_  REFGUID guid,
        _In_  UINT DataSize,
        _In_reads_bytes_opt_( DataSize )  const void *pData) override;

    HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(
        _In_  REFGUID guid,
        _In_opt_  const IUnknown *pData) override;

    HRESULT STDMETHODCALLTYPE SetName(
        _In_z_  LPCWSTR Name) override;

    HRESULT STDMETHODCALLTYPE GetDevice(
        REFIID riid,
        _COM_Outptr_opt_  void **ppvDevice) override;

    HRESULT STDMETHODCALLTYPE GetCachedBlob(
    _COM_Outptr_  ID3DBlob **ppBlob) override;

    bool isGraphics() const;

    id<MTLRenderPipelineState> GetRenderPipelineState() const;

    MTLCullMode GetCullMode() const;

private:
    id<MTLFunction> CreateFunction(const D3D12_SHADER_BYTECODE& bytecode);

private:
    id<MTLRenderPipelineState> render_pipeline_state_ = { nil };
    MTLCullMode cull_mode_;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_D3D12_PIPELINE_STATE_H_
