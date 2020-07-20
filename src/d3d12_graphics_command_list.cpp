//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_graphics_command_list.h"

#include <cassert>

#include "dxgi_swap_chain.h"
#include "d3d12_helper.h"
#include "d3d12_command_allocator.h"
#include "d3d12_pipeline_state.h"
#include "d3d12_buffer.h"
#include "d3d12_texture.h"
#include "metal_helper.h"

//----------------------------------------------------------------------------------------------------------------------

D3D12GraphicsCommandList::D3D12GraphicsCommandList(D3D12Device* device_ptr)
: D3D12CommandList(device_ptr) {
    vertex_buffers_.fill(nullptr);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12GraphicsCommandList::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return D3D12CommandList::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12GraphicsCommandList::AddRef( void) {
    return D3D12CommandList::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12GraphicsCommandList::Release( void) {
    return D3D12CommandList::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12GraphicsCommandList::GetPrivateData(
    _In_  REFGUID guid,
    _Inout_  UINT *pDataSize,
    _Out_writes_bytes_opt_( *pDataSize )  void *pData) {
    return D3D12CommandList::GetPrivateData(guid, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12GraphicsCommandList::SetPrivateData(
    _In_  REFGUID guid,
    _In_  UINT DataSize,
    _In_reads_bytes_opt_( DataSize )  const void *pData) {
    return D3D12CommandList::SetPrivateData(guid, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12GraphicsCommandList::SetPrivateDataInterface(
    _In_  REFGUID guid,
    _In_opt_  const IUnknown *pData) {
    return D3D12CommandList::SetPrivateDataInterface(guid, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12GraphicsCommandList::SetName(
    _In_z_  LPCWSTR Name) {
    return D3D12CommandList::SetName(Name);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12GraphicsCommandList::GetDevice(
    REFIID riid,
    _COM_Outptr_opt_  void **ppvDevice) {
    return D3D12CommandList::GetDevice(riid, ppvDevice);
}

//----------------------------------------------------------------------------------------------------------------------

D3D12_COMMAND_LIST_TYPE STDMETHODCALLTYPE D3D12GraphicsCommandList::GetType( void) {
    return D3D12CommandList::GetType();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12GraphicsCommandList::Close( void) {
    if (!GetCommandAllocator()) {
        return S_OK;
    }

    if (!render_command_encoder_) {
        return E_FAIL;
    }

    [render_command_encoder_ endEncoding];
    render_command_encoder_= nil;

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12GraphicsCommandList::Reset(
    _In_  ID3D12CommandAllocator *pAllocator,
    _In_opt_  ID3D12PipelineState *pInitialState) {
    SetCommandAllocator(dynamic_cast<D3D12CommandAllocator*>(pAllocator));

    if (pInitialState) {
        pipeline_state_ = dynamic_cast<D3D12PipelineState*>(pInitialState);
        assert(pipeline_state_);
    }

    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::ClearState(
    _In_opt_  ID3D12PipelineState *pPipelineState) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::DrawInstanced(
    _In_  UINT VertexCountPerInstance,
    _In_  UINT InstanceCount,
    _In_  UINT StartVertexLocation,
    _In_  UINT StartInstanceLocation) {
    [render_command_encoder_ drawPrimitives:primitive_type
                                vertexStart:StartVertexLocation
                                vertexCount:VertexCountPerInstance
                              instanceCount:InstanceCount
                               baseInstance:StartInstanceLocation];
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::DrawIndexedInstanced(
    _In_  UINT IndexCountPerInstance,
    _In_  UINT InstanceCount,
    _In_  UINT StartIndexLocation,
    _In_  INT BaseVertexLocation,
    _In_  UINT StartInstanceLocation) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::Dispatch(
    _In_  UINT ThreadGroupCountX,
    _In_  UINT ThreadGroupCountY,
    _In_  UINT ThreadGroupCountZ) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::CopyBufferRegion(
    _In_  ID3D12Resource *pDstBuffer,
    UINT64 DstOffset,
    _In_  ID3D12Resource *pSrcBuffer,
    UINT64 SrcOffset,
    UINT64 NumBytes) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::CopyTextureRegion(
    _In_  const D3D12_TEXTURE_COPY_LOCATION *pDst,
    UINT DstX,
    UINT DstY,
    UINT DstZ,
    _In_  const D3D12_TEXTURE_COPY_LOCATION *pSrc,
    _In_opt_  const D3D12_BOX *pSrcBox) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::CopyResource(
    _In_  ID3D12Resource *pDstResource,
    _In_  ID3D12Resource *pSrcResource) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::CopyTiles(
    _In_  ID3D12Resource *pTiledResource,
    _In_  const D3D12_TILED_RESOURCE_COORDINATE *pTileRegionStartCoordinate,
    _In_  const D3D12_TILE_REGION_SIZE *pTileRegionSize,
    _In_  ID3D12Resource *pBuffer,
    UINT64 BufferStartOffsetInBytes,
    D3D12_TILE_COPY_FLAGS Flags) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::ResolveSubresource(
    _In_  ID3D12Resource *pDstResource,
    _In_  UINT DstSubresource,
    _In_  ID3D12Resource *pSrcResource,
    _In_  UINT SrcSubresource,
    _In_  DXGI_FORMAT Format) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::IASetPrimitiveTopology(
    _In_  D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopology) {
    primitive_type = ToPrimitiveType(PrimitiveTopology);
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::RSSetViewports(
    _In_range_(0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT NumViewports,
    _In_reads_( NumViewports)  const D3D12_VIEWPORT *pViewports) {
    viewports_.resize(NumViewports);
    for (auto i = 0; i != NumViewports; ++i) {
        viewports_[i] = ToViewport(pViewports[i]);
    }

    if (render_command_encoder_) {
        [render_command_encoder_ setViewports:viewports_.data()
                                        count:viewports_.size()];
    }
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::RSSetScissorRects(
    _In_range_(0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT NumRects,
    _In_reads_( NumRects)  const D3D12_RECT *pRects) {
    scissor_rects_.resize(NumRects);
    for (auto i = 0; i != NumRects; ++i) {
        scissor_rects_[i] = ToScissorRect(pRects[i]);
    }

    if (render_command_encoder_) {
        [render_command_encoder_ setScissorRects:scissor_rects_.data()
                                           count:scissor_rects_.size()];
    }
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::OMSetBlendFactor(
    _In_reads_opt_(4)  const FLOAT BlendFactor[ 4 ]) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::OMSetStencilRef(
    _In_  UINT StencilRef) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetPipelineState(
    _In_  ID3D12PipelineState *pPipelineState) {
    if (!pPipelineState) {
        return;
    }

    pipeline_state_ = dynamic_cast<D3D12PipelineState*>(pPipelineState);
    assert(pipeline_state_);

    if (render_command_encoder_) {
        if (pipeline_state_->isGraphics()) {
            [render_command_encoder_ setRenderPipelineState:pipeline_state_->GetRenderPipelineState()];
            [render_command_encoder_ setCullMode:pipeline_state_->GetCullMode()];
        } else {
            assert(false && "Not implement!!!");
        }
        pipeline_state_= nullptr;
    }
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::ResourceBarrier(
    _In_  UINT NumBarriers,
    _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers) {
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::ExecuteBundle(
    _In_  ID3D12GraphicsCommandList *pCommandList) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetDescriptorHeaps(
    _In_  UINT NumDescriptorHeaps,
    _In_reads_(NumDescriptorHeaps)  ID3D12DescriptorHeap *const *ppDescriptorHeaps) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetComputeRootSignature(
    _In_opt_  ID3D12RootSignature *pRootSignature) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetGraphicsRootSignature(
    _In_opt_  ID3D12RootSignature *pRootSignature) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetComputeRootDescriptorTable(
    _In_  UINT RootParameterIndex,
    _In_  D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetGraphicsRootDescriptorTable(
    _In_  UINT RootParameterIndex,
    _In_  D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetComputeRoot32BitConstant(
    _In_  UINT RootParameterIndex,
    _In_  UINT SrcData,
    _In_  UINT DestOffsetIn32BitValues) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetGraphicsRoot32BitConstant(
    _In_  UINT RootParameterIndex,
    _In_  UINT SrcData,
    _In_  UINT DestOffsetIn32BitValues) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetComputeRoot32BitConstants(
    _In_  UINT RootParameterIndex,
    _In_  UINT Num32BitValuesToSet,
    _In_reads_(Num32BitValuesToSet*sizeof(UINT))  const void *pSrcData,
    _In_  UINT DestOffsetIn32BitValues) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetGraphicsRoot32BitConstants(
    _In_  UINT RootParameterIndex,
    _In_  UINT Num32BitValuesToSet,
    _In_reads_(Num32BitValuesToSet*sizeof(UINT))  const void *pSrcData,
    _In_  UINT DestOffsetIn32BitValues) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetComputeRootConstantBufferView(
    _In_  UINT RootParameterIndex,
    _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetGraphicsRootConstantBufferView(
    _In_  UINT RootParameterIndex,
    _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetComputeRootShaderResourceView(
    _In_  UINT RootParameterIndex,
    _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetGraphicsRootShaderResourceView(
    _In_  UINT RootParameterIndex,
    _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetComputeRootUnorderedAccessView(
    _In_  UINT RootParameterIndex,
    _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetGraphicsRootUnorderedAccessView(
    _In_  UINT RootParameterIndex,
    _In_  D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::IASetIndexBuffer(
    _In_opt_  const D3D12_INDEX_BUFFER_VIEW *pView) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::IASetVertexBuffers(
    _In_  UINT StartSlot,
    _In_  UINT NumViews,
    _In_reads_opt_(NumViews)  const D3D12_VERTEX_BUFFER_VIEW *pViews) {
    for (auto i = 0; i != NumViews; ++i) {
        auto buffer = reinterpret_cast<D3D12Buffer*>(pViews[i].BufferLocation);
        assert(buffer);

        if (render_command_encoder_) {
            buffer->BindAsVertexBuffer(render_command_encoder_, 0, StartSlot + i);
        } else {
            vertex_buffers_[StartSlot + i] = buffer;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SOSetTargets(
    _In_  UINT StartSlot,
    _In_  UINT NumViews,
    _In_reads_opt_(NumViews)  const D3D12_STREAM_OUTPUT_BUFFER_VIEW *pViews) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::OMSetRenderTargets(
    _In_  UINT NumRenderTargetDescriptors,
    _In_opt_  const D3D12_CPU_DESCRIPTOR_HANDLE *pRenderTargetDescriptors,
    _In_  BOOL RTsSingleHandleToDescriptorRange,
    _In_opt_  const D3D12_CPU_DESCRIPTOR_HANDLE *pDepthStencilDescriptor) {
    if (render_command_encoder_) {
        [render_command_encoder_ endEncoding];
        render_command_encoder_ = nil;
    }

    auto descriptor = [MTLRenderPassDescriptor new];

    for (auto i = 0; i != NumRenderTargetDescriptors; ++i) {
        auto texture = ToTexture(pRenderTargetDescriptors[i]);
        assert(texture);

        descriptor.colorAttachments[i].texture = texture->GetTexture();
        descriptor.colorAttachments[i].storeAction = MTLStoreActionStore;

        if (clear_colors_.find(texture) != std::end(clear_colors_)) {
            descriptor.colorAttachments[i].loadAction = MTLLoadActionClear;
            descriptor.colorAttachments[i].clearColor = clear_colors_[texture];
            clear_colors_.erase(texture);
        } else {
            descriptor.colorAttachments[i].loadAction = MTLLoadActionLoad;
        }
    }

    if (pDepthStencilDescriptor) {
        auto texture = ToTexture(*pDepthStencilDescriptor);
        assert(texture);

        descriptor.depthAttachment.texture = texture->GetTexture();
        descriptor.depthAttachment.storeAction = MTLStoreActionStore;

        if (clear_depths_.find(texture) != std::end(clear_depths_)) {
            descriptor.depthAttachment.loadAction = MTLLoadActionClear;
            descriptor.depthAttachment.clearDepth = clear_depths_[texture];
            clear_depths_.erase(texture);

        } else {
            descriptor.depthAttachment.loadAction = MTLLoadActionLoad;
        }

        descriptor.stencilAttachment.texture = texture->GetTexture();
        descriptor.stencilAttachment.storeAction = MTLStoreActionStore;

        if (clear_stencils_.find(texture) != std::end(clear_stencils_)) {
            descriptor.stencilAttachment.loadAction = MTLLoadActionClear;
            descriptor.stencilAttachment.clearStencil = clear_stencils_[texture];
            clear_stencils_.erase(texture);

        } else {
            descriptor.stencilAttachment.loadAction = MTLLoadActionLoad;
        }
    }

    auto command_buffer = command_allocator_ptr_->GetCommandBuffer();
    assert(command_buffer);

    render_command_encoder_ = [command_buffer renderCommandEncoderWithDescriptor:descriptor];
    assert(render_command_encoder_);

    if (!viewports_.empty()) {
        [render_command_encoder_ setViewports:viewports_.data()
                                        count:viewports_.size()];
        viewports_.clear();
    }

    if (!scissor_rects_.empty()) {
        [render_command_encoder_ setScissorRects:scissor_rects_.data()
                                           count:scissor_rects_.size()];
        scissor_rects_.clear();
    }

    if (pipeline_state_) {
        if (pipeline_state_->isGraphics()) {
            [render_command_encoder_ setRenderPipelineState:pipeline_state_->GetRenderPipelineState()];
            [render_command_encoder_ setCullMode:pipeline_state_->GetCullMode()];
        } else {
            assert(false && "Not implement!!!");
        }
        pipeline_state_= nullptr;
    }

    for (auto i = 0; i != 16; ++i) {
        if (!vertex_buffers_[i]) {
            continue;
        }

        vertex_buffers_[i]->BindAsVertexBuffer(render_command_encoder_, 0, i);
        vertex_buffers_[i] = nullptr;
    }
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::ClearDepthStencilView(
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView,
    _In_  D3D12_CLEAR_FLAGS ClearFlags,
    _In_  FLOAT Depth,
    _In_  UINT8 Stencil,
    _In_  UINT NumRects,
    _In_reads_(NumRects)  const D3D12_RECT *pRects) {
    auto resource = ToTexture(DepthStencilView);
    assert(resource);

    if (ClearFlags & D3D12_CLEAR_FLAG_DEPTH) {
        clear_depths_[resource] = Depth;
    }

    if (ClearFlags & D3D12_CLEAR_FLAG_STENCIL) {
        clear_stencils_[resource] = Stencil;
    }
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::ClearRenderTargetView(
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView,
    _In_  const FLOAT ColorRGBA[ 4 ],
    _In_  UINT NumRects,
    _In_reads_(NumRects)  const D3D12_RECT *pRects) {
    clear_colors_[ToTexture(RenderTargetView)] = ToClearColor(ColorRGBA);
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::ClearUnorderedAccessViewUint(
    _In_  D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle,
    _In_  ID3D12Resource *pResource,
    _In_  const UINT Values[ 4 ],
    _In_  UINT NumRects,
    _In_reads_(NumRects)  const D3D12_RECT *pRects) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::ClearUnorderedAccessViewFloat(
    _In_  D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
    _In_  D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle,
    _In_  ID3D12Resource *pResource,
    _In_  const FLOAT Values[ 4 ],
    _In_  UINT NumRects,
    _In_reads_(NumRects)  const D3D12_RECT *pRects) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::DiscardResource(
    _In_  ID3D12Resource *pResource,
    _In_opt_  const D3D12_DISCARD_REGION *pRegion) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::BeginQuery(
    _In_  ID3D12QueryHeap *pQueryHeap,
    _In_  D3D12_QUERY_TYPE Type,
    _In_  UINT Index) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::EndQuery(
    _In_  ID3D12QueryHeap *pQueryHeap,
    _In_  D3D12_QUERY_TYPE Type,
    _In_  UINT Index) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::ResolveQueryData(
    _In_  ID3D12QueryHeap *pQueryHeap,
    _In_  D3D12_QUERY_TYPE Type,
    _In_  UINT StartIndex,
    _In_  UINT NumQueries,
    _In_  ID3D12Resource *pDestinationBuffer,
    _In_  UINT64 AlignedDestinationBufferOffset) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetPredication(
    _In_opt_  ID3D12Resource *pBuffer,
    _In_  UINT64 AlignedBufferOffset,
    _In_  D3D12_PREDICATION_OP Operation) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::SetMarker(
    UINT Metadata,
    _In_reads_bytes_opt_(Size)  const void *pData,
    UINT Size) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::BeginEvent(
    UINT Metadata,
    _In_reads_bytes_opt_(Size)  const void *pData,
    UINT Size) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::EndEvent( void) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------

void STDMETHODCALLTYPE D3D12GraphicsCommandList::ExecuteIndirect(
    _In_  ID3D12CommandSignature *pCommandSignature,
    _In_  UINT MaxCommandCount,
    _In_  ID3D12Resource *pArgumentBuffer,
    _In_  UINT64 ArgumentBufferOffset,
    _In_opt_  ID3D12Resource *pCountBuffer,
    _In_  UINT64 CountBufferOffset) {
    assert(false && "Not implement!!!");
}

//----------------------------------------------------------------------------------------------------------------------
