//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_D3D12_DESCRIPTOR_HEAP_H_
#define DX12_D3D12_DESCRIPTOR_HEAP_H_

#include <vector>

#include "d3d12.h"
#include "d3d12_pageable.h"

//----------------------------------------------------------------------------------------------------------------------

class D3D12Resource;

//----------------------------------------------------------------------------------------------------------------------

class D3D12DescriptorHeap : ID3D12DescriptorHeap, public D3D12Pageable {
public:
    D3D12DescriptorHeap(D3D12Device* device_ptr, const D3D12_DESCRIPTOR_HEAP_DESC* desc_ptr);

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

    D3D12_DESCRIPTOR_HEAP_DESC STDMETHODCALLTYPE GetDesc( void) override;

    D3D12_CPU_DESCRIPTOR_HANDLE STDMETHODCALLTYPE GetCPUDescriptorHandleForHeapStart( void) override;

    D3D12_GPU_DESCRIPTOR_HANDLE STDMETHODCALLTYPE GetGPUDescriptorHandleForHeapStart( void) override;

private:
    D3D12_DESCRIPTOR_HEAP_DESC desc_;
    std::vector<D3D12Resource*> resource_ptrs_;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_D3D12_DESCRIPTOR_HEAP_H_
