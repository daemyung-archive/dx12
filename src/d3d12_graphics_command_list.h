//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_D3D12_GRAPHICS_COMMAND_LIST_H_
#define DX12_D3D12_GRAPHICS_COMMAND_LIST_H_

#include <vector>
#include <unordered_map>

#include "d3d12.h"
#include "d3d12_command_list.h"
#include "metal_library.h"

//----------------------------------------------------------------------------------------------------------------------

class D3D12PipelineState;
class D3D12Resource;

//----------------------------------------------------------------------------------------------------------------------

class D3D12GraphicsCommandList : public ID3D12GraphicsCommandList, public D3D12CommandList {
public:
    D3D12GraphicsCommandList(D3D12Device* device_ptr);

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

    D3D12_COMMAND_LIST_TYPE STDMETHODCALLTYPE GetType( void) override;

    HRESULT STDMETHODCALLTYPE Close( void) override;

    HRESULT STDMETHODCALLTYPE Reset(
        _In_  ID3D12CommandAllocator *pAllocator,
        _In_opt_  ID3D12PipelineState *pInitialState) override;

    void STDMETHODCALLTYPE ClearState(
        _In_opt_  ID3D12PipelineState *pPipelineState) override;

    void STDMETHODCALLTYPE DrawInstanced(
        _In_  UINT VertexCountPerInstance,
        _In_  UINT InstanceCount,
        _In_  UINT StartVertexLocation,
        _In_  UINT StartInstanceLocation) override;

    void STDMETHODCALLTYPE DrawIndexedInstanced(
        _In_  UINT IndexCountPerInstance,
        _In_  UINT InstanceCount,
        _In_  UINT StartIndexLocation,
        _In_  INT BaseVertexLocation,
        _In_  UINT StartInstanceLocation) override;

    void STDMETHODCALLTYPE Dispatch(
        _In_  UINT ThreadGroupCountX,
        _In_  UINT ThreadGroupCountY,
        _In_  UINT ThreadGroupCountZ) override;

    void STDMETHODCALLTYPE CopyBufferRegion(
        _In_  ID3D12Resource *pDstBuffer,
        UINT64 DstOffset,
        _In_  ID3D12Resource *pSrcBuffer,
        UINT64 SrcOffset,
        UINT64 NumBytes) override;

    void STDMETHODCALLTYPE CopyTextureRegion(
        _In_  const D3D12_TEXTURE_COPY_LOCATION *pDst,
        UINT DstX,
        UINT DstY,
        UINT DstZ,
        _In_  const D3D12_TEXTURE_COPY_LOCATION *pSrc,
        _In_opt_  const D3D12_BOX *pSrcBox) override;

    void STDMETHODCALLTYPE CopyResource(
        _In_  ID3D12Resource *pDstResource,
        _In_  ID3D12Resource *pSrcResource) override;

    void STDMETHODCALLTYPE CopyTiles(
        _In_  ID3D12Resource *pTiledResource,
        _In_  const D3D12_TILED_RESOURCE_COORDINATE *pTileRegionStartCoordinate,
        _In_  const D3D12_TILE_REGION_SIZE *pTileRegionSize,
        _In_  ID3D12Resource *pBuffer,
        UINT64 BufferStartOffsetInBytes,
        D3D12_TILE_COPY_FLAGS Flags) override;

    void STDMETHODCALLTYPE ResolveSubresource(
        _In_  ID3D12Resource *pDstResource,
        _In_  UINT DstSubresource,
        _In_  ID3D12Resource *pSrcResource,
        _In_  UINT SrcSubresource,
        _In_  DXGI_FORMAT Format) override;

    void STDMETHODCALLTYPE IASetPrimitiveTopology(
        _In_  D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopology) override;

    void STDMETHODCALLTYPE RSSetViewports(
        _In_range_(0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT NumViewports,
        _In_reads_( NumViewports)  const D3D12_VIEWPORT *pViewports) override;

    void STDMETHODCALLTYPE RSSetScissorRects(
        _In_range_(0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT NumRects,
        _In_reads_( NumRects)  const D3D12_RECT *pRects) override;

    void STDMETHODCALLTYPE OMSetBlendFactor(
        _In_reads_opt_(4)  const FLOAT BlendFactor[ 4 ]) override;

    void STDMETHODCALLTYPE OMSetStencilRef(
        _In_  UINT StencilRef) override;

    void STDMETHODCALLTYPE SetPipelineState(
        _In_  ID3D12PipelineState *pPipelineState) override;

    void STDMETHODCALLTYPE ResourceBarrier(
        _In_  UINT NumBarriers,
        _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers) override;

    void STDMETHODCALLTYPE ExecuteBundle(
        _In_  ID3D12GraphicsCommandList *pCommandList) override;

    void STDMETHODCALLTYPE SetDescriptorHeaps(
        _In_  UINT NumDescriptorHeaps,
        _In_reads_(NumDescriptorHeaps)  ID3D12DescriptorHeap *const *ppDescriptorHeaps) override;

    void STDMETHODCALLTYPE SetComputeRootSignature(
        _In_opt_  ID3D12RootSignature *pRootSignature) override;

    void STDMETHODCALLTYPE SetGraphicsRootSignature(
        _In_opt_  ID3D12RootSignature *pRootSignature) override;

    void STDMETHODCALLTYPE SetComputeRootDescriptorTable(
        _In_  UINT RootParameterIndex,
        _In_  D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor) override;

    void STDMETHODCALLTYPE SetGraphicsRootDescriptorTable(
        _In_  UINT RootParameterIndex,
        _In_  D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor) override;

    void STDMETHODCALLTYPE SetComputeRoot32BitConstant(
        _In_  UINT RootParameterIndex,
        _In_  UINT SrcData,
        _In_  UINT DestOffsetIn32BitValues) override;

    void STDMETHODCALLTYPE SetGraphicsRoot32BitConstant(
        _In_  UINT RootParameterIndex,
        _In_  UINT SrcData,
        _In_  UINT DestOffsetIn32BitValues) override;

    void STDMETHODCALLTYPE SetComputeRoot32BitConstants(
        _In_  UINT RootParameterIndex,
        _In_  UINT Num32BitValuesToSet,
        _In_reads_(Num32BitValuesToSet*sizeof(UINT))  const void *pSrcData,
        _In_  UINT DestOffsetIn32BitValues) override;

    void STDMETHODCALLTYPE SetGraphicsRoot32BitConstants(
        _In_  UINT RootParameterIndex,
        _In_  UINT Num32BitValuesToSet,
        _In_reads_(Num32BitValuesToSet*sizeof(UINT))  const void *pSrcData,
        _In_  UINT DestOffsetIn32BitValues) override;

    void STDMETHODCALLTYPE SetComputeRootConstantBufferView(
        _In_  UINT RootParameterIndex,
        _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) override;

    void STDMETHODCALLTYPE SetGraphicsRootConstantBufferView(
        _In_  UINT RootParameterIndex,
        _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) override;

    void STDMETHODCALLTYPE SetComputeRootShaderResourceView(
        _In_  UINT RootParameterIndex,
        _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) override;

    void STDMETHODCALLTYPE SetGraphicsRootShaderResourceView(
        _In_  UINT RootParameterIndex,
        _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) override;

    void STDMETHODCALLTYPE SetComputeRootUnorderedAccessView(
        _In_  UINT RootParameterIndex,
        _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) override;

    void STDMETHODCALLTYPE SetGraphicsRootUnorderedAccessView(
        _In_  UINT RootParameterIndex,
        _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) override;

    void STDMETHODCALLTYPE IASetIndexBuffer(
        _In_opt_  const D3D12_INDEX_BUFFER_VIEW *pView) override;

    void STDMETHODCALLTYPE IASetVertexBuffers(
        _In_  UINT StartSlot,
        _In_  UINT NumViews,
        _In_reads_opt_(NumViews)  const D3D12_VERTEX_BUFFER_VIEW *pViews) override;

    void STDMETHODCALLTYPE SOSetTargets(
        _In_  UINT StartSlot,
        _In_  UINT NumViews,
        _In_reads_opt_(NumViews)  const D3D12_STREAM_OUTPUT_BUFFER_VIEW *pViews) override;

    void STDMETHODCALLTYPE OMSetRenderTargets(
        _In_  UINT NumRenderTargetDescriptors,
        _In_opt_  const D3D12_CPU_DESCRIPTOR_HANDLE *pRenderTargetDescriptors,
        _In_  BOOL RTsSingleHandleToDescriptorRange,
        _In_opt_  const D3D12_CPU_DESCRIPTOR_HANDLE *pDepthStencilDescriptor) override;

    void STDMETHODCALLTYPE ClearDepthStencilView(
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView,
        _In_  D3D12_CLEAR_FLAGS ClearFlags,
        _In_  FLOAT Depth,
        _In_  UINT8 Stencil,
        _In_  UINT NumRects,
        _In_reads_(NumRects)  const D3D12_RECT *pRects) override;

    void STDMETHODCALLTYPE ClearRenderTargetView(
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView,
        _In_  const FLOAT ColorRGBA[ 4 ],
        _In_  UINT NumRects,
        _In_reads_(NumRects)  const D3D12_RECT *pRects) override;

    void STDMETHODCALLTYPE ClearUnorderedAccessViewUint(
        _In_  D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle,
        _In_  ID3D12Resource *pResource,
        _In_  const UINT Values[ 4 ],
        _In_  UINT NumRects,
        _In_reads_(NumRects)  const D3D12_RECT *pRects) override;

    void STDMETHODCALLTYPE ClearUnorderedAccessViewFloat(
        _In_  D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
        _In_  D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle,
        _In_  ID3D12Resource *pResource,
        _In_  const FLOAT Values[ 4 ],
        _In_  UINT NumRects,
        _In_reads_(NumRects)  const D3D12_RECT *pRects) override;

    void STDMETHODCALLTYPE DiscardResource(
        _In_  ID3D12Resource *pResource,
        _In_opt_  const D3D12_DISCARD_REGION *pRegion) override;

    void STDMETHODCALLTYPE BeginQuery(
        _In_  ID3D12QueryHeap *pQueryHeap,
        _In_  D3D12_QUERY_TYPE Type,
        _In_  UINT Index) override;

    void STDMETHODCALLTYPE EndQuery(
        _In_  ID3D12QueryHeap *pQueryHeap,
        _In_  D3D12_QUERY_TYPE Type,
        _In_  UINT Index) override;

    void STDMETHODCALLTYPE ResolveQueryData(
        _In_  ID3D12QueryHeap *pQueryHeap,
        _In_  D3D12_QUERY_TYPE Type,
        _In_  UINT StartIndex,
        _In_  UINT NumQueries,
        _In_  ID3D12Resource *pDestinationBuffer,
        _In_  UINT64 AlignedDestinationBufferOffset) override;

    void STDMETHODCALLTYPE SetPredication(
        _In_opt_  ID3D12Resource *pBuffer,
        _In_  UINT64 AlignedBufferOffset,
        _In_  D3D12_PREDICATION_OP Operation) override;

    void STDMETHODCALLTYPE SetMarker(
        UINT Metadata,
        _In_reads_bytes_opt_(Size)  const void *pData,
        UINT Size) override;

    void STDMETHODCALLTYPE BeginEvent(
        UINT Metadata,
        _In_reads_bytes_opt_(Size)  const void *pData,
        UINT Size) override;

    void STDMETHODCALLTYPE EndEvent( void) override;

    void STDMETHODCALLTYPE ExecuteIndirect(
        _In_  ID3D12CommandSignature *pCommandSignature,
        _In_  UINT MaxCommandCount,
        _In_  ID3D12Resource *pArgumentBuffer,
        _In_  UINT64 ArgumentBufferOffset,
        _In_opt_  ID3D12Resource *pCountBuffer,
        _In_  UINT64 CountBufferOffset) override;

private:
    id<MTLRenderCommandEncoder> render_command_encoder_ = { nil };
    std::unordered_map<D3D12Resource*, MTLClearColor> clear_colors_;
    std::unordered_map<D3D12Resource*, float> clear_depths_;
    std::unordered_map<D3D12Resource*, uint8_t> clear_stencils_;
    std::vector<MTLViewport> viewports_;
    std::vector<MTLScissorRect> scissor_rects_;
    D3D12PipelineState* pipeline_state_ = { nullptr };
    std::vector<D3D12Resource*> vertex_buffers_;
    MTLPrimitiveType primitive_type;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_D3D12_GRAPHICS_COMMAND_LIST_H_
