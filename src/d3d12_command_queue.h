//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_D3D12_COMMAND_QUEUE_H_
#define DX12_D3D12_COMMAND_QUEUE_H_

#include "d3d12.h"
#include "d3d12_pageable.h"
#include "metal_library.h"

//----------------------------------------------------------------------------------------------------------------------

class D3D12CommandQueue : public ID3D12CommandQueue, public D3D12Pageable {
public:
    D3D12CommandQueue(D3D12Device* device_ptr, const D3D12_COMMAND_QUEUE_DESC* desc_ptr);

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

    void STDMETHODCALLTYPE UpdateTileMappings(
        _In_  ID3D12Resource *pResource,
        UINT NumResourceRegions,
        _In_reads_opt_(NumResourceRegions)  const D3D12_TILED_RESOURCE_COORDINATE *pResourceRegionStartCoordinates,
        _In_reads_opt_(NumResourceRegions)  const D3D12_TILE_REGION_SIZE *pResourceRegionSizes,
        _In_opt_  ID3D12Heap *pHeap,
        UINT NumRanges,
        _In_reads_opt_(NumRanges)  const D3D12_TILE_RANGE_FLAGS *pRangeFlags,
        _In_reads_opt_(NumRanges)  const UINT *pHeapRangeStartOffsets,
        _In_reads_opt_(NumRanges)  const UINT *pRangeTileCounts,
        D3D12_TILE_MAPPING_FLAGS Flags) override;

    void STDMETHODCALLTYPE CopyTileMappings(
        _In_  ID3D12Resource *pDstResource,
        _In_  const D3D12_TILED_RESOURCE_COORDINATE *pDstRegionStartCoordinate,
        _In_  ID3D12Resource *pSrcResource,
        _In_  const D3D12_TILED_RESOURCE_COORDINATE *pSrcRegionStartCoordinate,
        _In_  const D3D12_TILE_REGION_SIZE *pRegionSize,
        D3D12_TILE_MAPPING_FLAGS Flags) override;

    void STDMETHODCALLTYPE ExecuteCommandLists(
        _In_  UINT NumCommandLists,
        _In_reads_(NumCommandLists)  ID3D12CommandList *const *ppCommandLists) override;

    void STDMETHODCALLTYPE SetMarker(
        UINT Metadata,
        _In_reads_bytes_opt_(Size)  const void *pData,
        UINT Size) override;

    void STDMETHODCALLTYPE BeginEvent(
        UINT Metadata,
        _In_reads_bytes_opt_(Size)  const void *pData,
        UINT Size) override;

    void STDMETHODCALLTYPE EndEvent( void) override;

    HRESULT STDMETHODCALLTYPE Signal(
        ID3D12Fence *pFence,
        UINT64 Value) override;

    HRESULT STDMETHODCALLTYPE Wait(
        ID3D12Fence *pFence,
        UINT64 Value) override;

    HRESULT STDMETHODCALLTYPE GetTimestampFrequency(
        _Out_  UINT64 *pFrequency) override;

    HRESULT STDMETHODCALLTYPE GetClockCalibration(
        _Out_  UINT64 *pGpuTimestamp,
        _Out_  UINT64 *pCpuTimestamp) override;

    D3D12_COMMAND_QUEUE_DESC STDMETHODCALLTYPE GetDesc( void) override;

    id<MTLCommandQueue> GetCommandQueue() const;

private:
    D3D12_COMMAND_QUEUE_DESC desc_;
    id<MTLCommandQueue> command_queue_ = { nil };
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_D3D12_COMMAND_QUEUE_H_
