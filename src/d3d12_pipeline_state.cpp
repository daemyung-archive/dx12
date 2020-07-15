//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "d3d12_pipeline_state.h"

#include <cassert>
#include <spirv_cross/spirv_reflect.hpp>
#include <spirv_cross/spirv_msl.hpp>
#include <rapidjson/document.h>

#include "d3d12_device.h"
#include "metal_helper.h"

//----------------------------------------------------------------------------------------------------------------------

using namespace spirv_cross;
using namespace rapidjson;

//----------------------------------------------------------------------------------------------------------------------

D3D12PipelineState::D3D12PipelineState(D3D12Device* device, const D3D12_GRAPHICS_PIPELINE_STATE_DESC* desc)
: D3D12Pageable(device) {
    auto descriptor = [MTLRenderPipelineDescriptor new];
    assert(descriptor);

    descriptor.vertexFunction = CreateFunction(desc->VS);
    descriptor.fragmentFunction = CreateFunction(desc->PS);

    for (auto i = 0; i != desc->InputLayout.NumElements; ++i) {
        descriptor.vertexDescriptor.layouts[i + 16].stride +=
            GetSize(desc->InputLayout.pInputElementDescs[i].Format);
        descriptor.vertexDescriptor.layouts[i + 16].stepRate =
            desc->InputLayout.pInputElementDescs[i].InstanceDataStepRate;
        descriptor.vertexDescriptor.layouts[i + 16].stepFunction =
            ToVertexStepFunction(desc->InputLayout.pInputElementDescs[i].InputSlotClass);
    }

    for (auto i = 0; i != desc->InputLayout.NumElements; ++i) {
        descriptor.vertexDescriptor.attributes[i].format =
            ToVertexFormat(desc->InputLayout.pInputElementDescs[i].Format);
        descriptor.vertexDescriptor.attributes[i].offset =
            desc->InputLayout.pInputElementDescs[i].AlignedByteOffset;
        descriptor.vertexDescriptor.attributes[i].bufferIndex =
            desc->InputLayout.pInputElementDescs[i].InputSlot + 16;
    }

    descriptor.sampleCount = desc->SampleDesc.Count;
    descriptor.rasterSampleCount = desc->SampleDesc.Count;

    for (auto i = 0; i != desc->NumRenderTargets; ++i) {
        descriptor.colorAttachments[i].pixelFormat = ToPixelFormat(desc->RTVFormats[i]);
        descriptor.colorAttachments[i].writeMask =
            desc->BlendState.RenderTarget[i].RenderTargetWriteMask;

        if (desc->BlendState.IndependentBlendEnable) {
            descriptor.colorAttachments[i].blendingEnabled =
                desc->BlendState.RenderTarget[i].BlendEnable;
        } else {
            descriptor.colorAttachments[i].blendingEnabled =
                desc->BlendState.RenderTarget[0].BlendEnable;
        }

        descriptor.colorAttachments[i].sourceRGBBlendFactor =
            ToBlendFactor(desc->BlendState.RenderTarget[i].SrcBlend);
        descriptor.colorAttachments[i].destinationRGBBlendFactor =
            ToBlendFactor(desc->BlendState.RenderTarget[i].DestBlend);
        descriptor.colorAttachments[i].rgbBlendOperation =
            ToBlendOperation(desc->BlendState.RenderTarget[i].BlendOp);
        descriptor.colorAttachments[i].sourceAlphaBlendFactor =
            ToBlendFactor(desc->BlendState.RenderTarget[i].SrcBlendAlpha);
        descriptor.colorAttachments[i].destinationAlphaBlendFactor =
            ToBlendFactor(desc->BlendState.RenderTarget[i].DestBlendAlpha);
        descriptor.colorAttachments[i].alphaBlendOperation =
            ToBlendOperation(desc->BlendState.RenderTarget[i].BlendOpAlpha);
    }

    if (desc->DSVFormat != DXGI_FORMAT_UNKNOWN) {
        descriptor.depthAttachmentPixelFormat = ToPixelFormat(desc->DSVFormat);
        descriptor.stencilAttachmentPixelFormat = ToPixelFormat(desc->DSVFormat);
    }

    descriptor.inputPrimitiveTopology = ToPrimitiveTopologyClass(desc->PrimitiveTopologyType);

    render_pipeline_state_ = [device_->GetDevice() newRenderPipelineStateWithDescriptor:descriptor
                                                                                  error:nil];
    assert(render_pipeline_state_);

    cull_mode_ = ToCullMode(desc->RasterizerState.CullMode);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12PipelineState::QueryInterface(
    REFIID riid,
    void **ppvObject) {
    return D3D12Pageable::QueryInterface(riid, ppvObject);
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12PipelineState::AddRef( void) {
    return D3D12Pageable::AddRef();
}

//----------------------------------------------------------------------------------------------------------------------

ULONG STDMETHODCALLTYPE D3D12PipelineState::Release( void) {
    return D3D12Pageable::Release();
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12PipelineState::GetPrivateData(
    _In_  REFGUID guid,
    _Inout_  UINT *pDataSize,
    _Out_writes_bytes_opt_( *pDataSize )  void *pData) {
    return D3D12Pageable::GetPrivateData(guid, pDataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12PipelineState::SetPrivateData(
    _In_  REFGUID guid,
    _In_  UINT DataSize,
    _In_reads_bytes_opt_( DataSize )  const void *pData) {
    return D3D12Pageable::SetPrivateData(guid, DataSize, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12PipelineState::SetPrivateDataInterface(
    _In_  REFGUID guid,
    _In_opt_  const IUnknown *pData) {
    return D3D12Pageable::SetPrivateDataInterface(guid, pData);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12PipelineState::SetName(
    _In_z_  LPCWSTR Name) {
    return D3D12Pageable::SetName(Name);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12PipelineState::GetDevice(
    REFIID riid,
    _COM_Outptr_opt_  void **ppvDevice) {
    return D3D12Pageable::GetDevice(riid, ppvDevice);
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE D3D12PipelineState::GetCachedBlob(
    _COM_Outptr_  ID3DBlob **ppBlob) {
    assert(false && "Not implement!!!");
    return S_OK;
}

//----------------------------------------------------------------------------------------------------------------------

bool D3D12PipelineState::isGraphics() const {
    return render_pipeline_state_ != nil;
}

//----------------------------------------------------------------------------------------------------------------------

id<MTLRenderPipelineState> D3D12PipelineState::GetRenderPipelineState() const {
    return render_pipeline_state_;
}

//----------------------------------------------------------------------------------------------------------------------

MTLCullMode D3D12PipelineState::GetCullMode() const {
    return cull_mode_;
}

//----------------------------------------------------------------------------------------------------------------------

id<MTLFunction> D3D12PipelineState::CreateFunction(const D3D12_SHADER_BYTECODE& bytecode) {
    auto spirv = static_cast<const uint32_t*>(bytecode.pShaderBytecode);
    auto count = bytecode.BytecodeLength / sizeof(uint32_t);

    CompilerMSL compiler(spirv, count);
    auto msl = compiler.compile();

    auto library = [device_->GetDevice() newLibraryWithSource:@(msl.c_str())
                                                      options:nullptr
                                                        error:nil];
    assert(library);

    CompilerReflection reflector(spirv, count);
    auto manifest = reflector.compile();

    Document document;
    document.Parse(manifest.data());

    auto entry_point = document["entryPoints"][0]["name"].GetString();
    auto function = [library newFunctionWithName:@(entry_point)];
    assert(function);

    return function;
}

//----------------------------------------------------------------------------------------------------------------------
