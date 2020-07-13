//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_device.h"

#include <cassert>

#include "d3d12_command_queue.h"
#include "d3d12_command_allocator.h"
#include "d3d12_graphics_command_list.h"
#include "d3d12_descriptor_heap.h"
#include "d3d12_resource.h"

//----------------------------------------------------------------------------------------------------------------------

D3D12Device::D3D12Device() {
    device_ = MTLCreateSystemDefaultDevice();
}

//----------------------------------------------------------------------------------------------------------------------

D3D12Device::D3D12Device(id<MTLDevice> device)
: device_(device) {
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return D3D12Object::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12Device::AddRef( void) {
    return D3D12Object::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12Device::Release( void) {
    return D3D12Object::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::GetPrivateData(
    _In_  REFGUID guid,
    _Inout_  UINT *pDataSize,
    _Out_writes_bytes_opt_( *pDataSize )  void *pData) {
    return D3D12Object::GetPrivateData(guid, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::SetPrivateData(
    _In_  REFGUID guid,
    _In_  UINT DataSize,
    _In_reads_bytes_opt_( DataSize )  const void *pData) {
    return D3D12Object::SetPrivateData(guid, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::SetPrivateDataInterface(
    _In_  REFGUID guid,
    _In_opt_  const IUnknown *pData) {
    return D3D12Object::SetPrivateDataInterface(guid, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::SetName(
    _In_z_  LPCWSTR Name) {
    return D3D12Object::SetName(Name);
}

//----------------------------------------------------------------------------------------------------------------------

UINT STDMETHODCALLTYPE D3D12Device::GetNodeCount( void) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateCommandQueue(
    _In_  const D3D12_COMMAND_QUEUE_DESC *pDesc,
    REFIID riid,
    _COM_Outptr_  void **ppCommandQueue) {
    if (!command_queue_) {
        command_queue_ = [device_ newCommandQueue];
        assert(command_queue_);
    }

    *ppCommandQueue = new D3D12CommandQueue(this, pDesc);
    assert(*ppCommandQueue);

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateCommandAllocator(
    _In_  D3D12_COMMAND_LIST_TYPE type,
    REFIID riid,
    _COM_Outptr_  void **ppCommandAllocator) {
    *ppCommandAllocator = new D3D12CommandAllocator(this);
    assert(*ppCommandAllocator);

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateGraphicsPipelineState(
    _In_  const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc,
    REFIID riid,
    _COM_Outptr_  void **ppPipelineState) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateComputePipelineState(
    _In_  const D3D12_COMPUTE_PIPELINE_STATE_DESC *pDesc,
    REFIID riid,
    _COM_Outptr_  void **ppPipelineState) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateCommandList(
    _In_  UINT nodeMask,
    _In_  D3D12_COMMAND_LIST_TYPE type,
    _In_  ID3D12CommandAllocator *pCommandAllocator,
    _In_opt_  ID3D12PipelineState *pInitialState,
    REFIID riid,
    _COM_Outptr_  void **ppCommandList) {
    *ppCommandList = new D3D12GraphicsCommandList(this);
    assert(*ppCommandList);

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CheckFeatureSupport(
    D3D12_FEATURE Feature,
    _Inout_updates_bytes_(FeatureSupportDataSize)  void *pFeatureSupportData,
    UINT FeatureSupportDataSize) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateDescriptorHeap(
    _In_  const D3D12_DESCRIPTOR_HEAP_DESC *pDescriptorHeapDesc,
    REFIID riid,
    _COM_Outptr_  void **ppvHeap) {
    *ppvHeap = new D3D12DescriptorHeap(this, pDescriptorHeapDesc);
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

UINT STDMETHODCALLTYPE D3D12Device::GetDescriptorHandleIncrementSize(
    _In_  D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType) {
    return sizeof(D3D12Resource*);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateRootSignature(
    _In_  UINT nodeMask,
    _In_reads_(blobLengthInBytes)  const void *pBlobWithRootSignature,
    _In_  SIZE_T blobLengthInBytes,
    REFIID riid,
    _COM_Outptr_  void **ppvRootSignature) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Device::CreateConstantBufferView(
    _In_opt_  const D3D12_CONSTANT_BUFFER_VIEW_DESC *pDesc,
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Device::CreateShaderResourceView(
    _In_opt_  ID3D12Resource *pResource,
    _In_opt_  const D3D12_SHADER_RESOURCE_VIEW_DESC *pDesc,
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Device::CreateUnorderedAccessView(
    _In_opt_  ID3D12Resource *pResource,
    _In_opt_  ID3D12Resource *pCounterResource,
    _In_opt_  const D3D12_UNORDERED_ACCESS_VIEW_DESC *pDesc,
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Device::CreateRenderTargetView(
    _In_opt_  ID3D12Resource *pResource,
    _In_opt_  const D3D12_RENDER_TARGET_VIEW_DESC *pDesc,
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) {
    memcpy(reinterpret_cast<void**>(DestDescriptor.ptr), &pResource, sizeof(D3D12Resource*));
    
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Device::CreateDepthStencilView(
    _In_opt_  ID3D12Resource *pResource,
    _In_opt_  const D3D12_DEPTH_STENCIL_VIEW_DESC *pDesc,
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) {
    memcpy(reinterpret_cast<void**>(DestDescriptor.ptr), &pResource, sizeof(D3D12Resource*));
    
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Device::CreateSampler(
    _In_  const D3D12_SAMPLER_DESC *pDesc,
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Device::CopyDescriptors(
    _In_  UINT NumDestDescriptorRanges,
    _In_reads_(NumDestDescriptorRanges)  const D3D12_CPU_DESCRIPTOR_HANDLE *pDestDescriptorRangeStarts,
    _In_reads_opt_(NumDestDescriptorRanges)  const UINT *pDestDescriptorRangeSizes,
    _In_  UINT NumSrcDescriptorRanges,
    _In_reads_(NumSrcDescriptorRanges)  const D3D12_CPU_DESCRIPTOR_HANDLE *pSrcDescriptorRangeStarts,
    _In_reads_opt_(NumSrcDescriptorRanges)  const UINT *pSrcDescriptorRangeSizes,
    _In_  D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Device::CopyDescriptorsSimple(
    _In_  UINT NumDescriptors,
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptorRangeStart,
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE SrcDescriptorRangeStart,
    _In_  D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE D3D12Device::GetResourceAllocationInfo(
    _In_  UINT visibleMask,
    _In_  UINT numResourceDescs,
    _In_reads_(numResourceDescs)  const D3D12_RESOURCE_DESC *pResourceDescs) {
    assert(false && "Not implement!!!");
    return D3D12_RESOURCE_ALLOCATION_INFO();
}

//----------------------------------------------------------------------------------------------------------------------

D3D12_HEAP_PROPERTIES STDMETHODCALLTYPE D3D12Device::GetCustomHeapProperties(
    _In_  UINT nodeMask,
    D3D12_HEAP_TYPE heapType) {
    assert(false && "Not implement!!!");
    return D3D12_HEAP_PROPERTIES();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateCommittedResource(
    _In_  const D3D12_HEAP_PROPERTIES *pHeapProperties,
    D3D12_HEAP_FLAGS HeapFlags,
    _In_  const D3D12_RESOURCE_DESC *pDesc,
    D3D12_RESOURCE_STATES InitialResourceState,
    _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
    REFIID riidResource,
    _COM_Outptr_opt_  void **ppvResource) {
    *ppvResource = new D3D12Resource(this, pHeapProperties, HeapFlags, pDesc, pOptimizedClearValue);
    assert(*ppvResource);

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateHeap(
    _In_  const D3D12_HEAP_DESC *pDesc,
    REFIID riid,
    _COM_Outptr_opt_  void **ppvHeap) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreatePlacedResource(
    _In_  ID3D12Heap *pHeap,
    UINT64 HeapOffset,
    _In_  const D3D12_RESOURCE_DESC *pDesc,
    D3D12_RESOURCE_STATES InitialState,
    _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
    REFIID riid,
    _COM_Outptr_opt_  void **ppvResource) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateReservedResource(
    _In_  const D3D12_RESOURCE_DESC *pDesc,
    D3D12_RESOURCE_STATES InitialState,
    _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
    REFIID riid,
    _COM_Outptr_opt_  void **ppvResource) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateSharedHandle(
    _In_  ID3D12DeviceChild *pObject,
    _In_opt_  const SECURITY_ATTRIBUTES *pAttributes,
    DWORD Access,
    _In_opt_  LPCWSTR Name,
    _Out_  HANDLE *pHandle) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::OpenSharedHandle(
    _In_  HANDLE NTHandle,
    REFIID riid,
    _COM_Outptr_opt_  void **ppvObj) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::OpenSharedHandleByName(
    _In_  LPCWSTR Name,
    DWORD Access,
    /* [annotation][out] */
    _Out_  HANDLE *pNTHandle) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::MakeResident(
    UINT NumObjects,
    _In_reads_(NumObjects)  ID3D12Pageable *const *ppObjects) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::Evict(
    UINT NumObjects,
    _In_reads_(NumObjects)  ID3D12Pageable *const *ppObjects) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateFence(
    UINT64 InitialValue,
    D3D12_FENCE_FLAGS Flags,
    REFIID riid,
    _COM_Outptr_  void **ppFence) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::GetDeviceRemovedReason( void) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Device::GetCopyableFootprints(
    _In_  const D3D12_RESOURCE_DESC *pResourceDesc,
    _In_range_(0,D3D12_REQ_SUBRESOURCES)  UINT FirstSubresource,
    _In_range_(0,D3D12_REQ_SUBRESOURCES-FirstSubresource)  UINT NumSubresources,
    UINT64 BaseOffset,
    _Out_writes_opt_(NumSubresources)  D3D12_PLACED_SUBRESOURCE_FOOTPRINT *pLayouts,
    _Out_writes_opt_(NumSubresources)  UINT *pNumRows,
    _Out_writes_opt_(NumSubresources)  UINT64 *pRowSizeInBytes,
    _Out_opt_  UINT64 *pTotalBytes) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateQueryHeap(
    _In_  const D3D12_QUERY_HEAP_DESC *pDesc,
    REFIID riid,
    _COM_Outptr_opt_  void **ppvHeap) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::SetStablePowerState(
    BOOL Enable) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12Device::CreateCommandSignature(
    _In_  const D3D12_COMMAND_SIGNATURE_DESC *pDesc,
    _In_opt_  ID3D12RootSignature *pRootSignature,
    REFIID riid,
    _COM_Outptr_opt_  void **ppvCommandSignature) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12Device::GetResourceTiling(
    _In_  ID3D12Resource *pTiledResource,
    _Out_opt_  UINT *pNumTilesForEntireResource,
    _Out_opt_  D3D12_PACKED_MIP_INFO *pPackedMipDesc,
    _Out_opt_  D3D12_TILE_SHAPE *pStandardTileShapeForNonPackedMips,
    _Inout_opt_  UINT *pNumSubresourceTilings,
    _In_  UINT FirstSubresourceTilingToGet,
    _Out_writes_(*pNumSubresourceTilings)  D3D12_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

LUID STDMETHODCALLTYPE D3D12Device::GetAdapterLuid( void) {
    assert(false && "Not implement!!!");
    return LUID();
}

//----------------------------------------------------------------------------------------------------------------------

id<MTLDevice> D3D12Device::GetDevice() const {
    return device_;
}

//----------------------------------------------------------------------------------------------------------------------

id<MTLCommandQueue> D3D12Device::GetCommandQueue() const {
    return command_queue_;
}

//----------------------------------------------------------------------------------------------------------------------
