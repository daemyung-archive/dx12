//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_command_queue.h"

#include <cassert>

#include "d3d12_device.h"
#include "d3d12_command_allocator.h"
#include "d3d12_graphics_command_list.h"

//----------------------------------------------------------------------------------------------------------------------

D3D12CommandQueue::D3D12CommandQueue(D3D12Device* device_ptr, const D3D12_COMMAND_QUEUE_DESC* desc_ptr)
: D3D12Pageable(device_ptr), desc_(*desc_ptr) {
    command_queue_ = device_ptr->GetCommandQueue();
    assert(command_queue_);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandQueue::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return D3D12Pageable::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12CommandQueue::AddRef( void) {
    return D3D12Pageable::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12CommandQueue::Release( void) {
    return D3D12Pageable::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandQueue::GetPrivateData(
    _In_  REFGUID guid,
    _Inout_  UINT *pDataSize,
    _Out_writes_bytes_opt_( *pDataSize )  void *pData) {
    return D3D12Pageable::GetPrivateData(guid, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandQueue::SetPrivateData(
    _In_  REFGUID guid,
    _In_  UINT DataSize,
    _In_reads_bytes_opt_( DataSize )  const void *pData) {
    return D3D12Pageable::SetPrivateData(guid, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandQueue::SetPrivateDataInterface(
    _In_  REFGUID guid,
    _In_opt_  const IUnknown *pData) {
    return D3D12Pageable::SetPrivateDataInterface(guid, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandQueue::SetName(
    _In_z_  LPCWSTR Name) {
    return D3D12Pageable::SetName(Name);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandQueue::GetDevice(
    REFIID riid,
    _COM_Outptr_opt_  void **ppvDevice) {
    return D3D12Pageable::GetDevice(riid, ppvDevice);
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12CommandQueue::UpdateTileMappings(
    _In_  ID3D12Resource *pResource,
    UINT NumResourceRegions,
    _In_reads_opt_(NumResourceRegions)  const D3D12_TILED_RESOURCE_COORDINATE *pResourceRegionStartCoordinates,
    _In_reads_opt_(NumResourceRegions)  const D3D12_TILE_REGION_SIZE *pResourceRegionSizes,
    _In_opt_  ID3D12Heap *pHeap,
    UINT NumRanges,
    _In_reads_opt_(NumRanges)  const D3D12_TILE_RANGE_FLAGS *pRangeFlags,
    _In_reads_opt_(NumRanges)  const UINT *pHeapRangeStartOffsets,
    _In_reads_opt_(NumRanges)  const UINT *pRangeTileCounts,
    D3D12_TILE_MAPPING_FLAGS Flags) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12CommandQueue::CopyTileMappings(
    _In_  ID3D12Resource *pDstResource,
    _In_  const D3D12_TILED_RESOURCE_COORDINATE *pDstRegionStartCoordinate,
    _In_  ID3D12Resource *pSrcResource,
    _In_  const D3D12_TILED_RESOURCE_COORDINATE *pSrcRegionStartCoordinate,
    _In_  const D3D12_TILE_REGION_SIZE *pRegionSize,
    D3D12_TILE_MAPPING_FLAGS Flags) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12CommandQueue::ExecuteCommandLists(
    _In_  UINT NumCommandLists,
    _In_reads_(NumCommandLists)  ID3D12CommandList *const *ppCommandLists) {
    for (auto i = 0; i != NumCommandLists; ++i) {
        auto command_list_ptr = dynamic_cast<D3D12CommandList*>(ppCommandLists[i]);
        assert(command_list_ptr);

        auto command_allocator_ptr = command_list_ptr->GetCommandAllocator();
        assert(command_allocator_ptr);

        auto command_buffer = command_allocator_ptr->GetCommandBuffer();
        assert(command_buffer);

        [command_buffer commit];
    }
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12CommandQueue::SetMarker(
    UINT Metadata,
    _In_reads_bytes_opt_(Size)  const void *pData,
    UINT Size) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12CommandQueue::BeginEvent(
    UINT Metadata,
    _In_reads_bytes_opt_(Size)  const void *pData,
    UINT Size) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12CommandQueue::EndEvent( void) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandQueue::Signal(
    ID3D12Fence *pFence,
    UINT64 Value) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandQueue::Wait(
    ID3D12Fence *pFence,
    UINT64 Value) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandQueue::GetTimestampFrequency(
    _Out_  UINT64 *pFrequency) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12CommandQueue::GetClockCalibration(
    _Out_  UINT64 *pGpuTimestamp,
    _Out_  UINT64 *pCpuTimestamp) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

D3D12_COMMAND_QUEUE_DESC STDMETHODCALLTYPE D3D12CommandQueue::GetDesc( void) {
    return desc_;
}

//----------------------------------------------------------------------------------------------------------------------

id<MTLCommandQueue> D3D12CommandQueue::GetCommandQueue() const {
    return command_queue_;
}

//----------------------------------------------------------------------------------------------------------------------
