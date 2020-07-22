//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "triangle_app.h"

#include <cassert>

//----------------------------------------------------------------------------------------------------------------------

struct Vertex {
    float position[2];
    float color[3];
};

//----------------------------------------------------------------------------------------------------------------------

TriangleApp::TriangleApp(GLFWwindow* window)
: App(window) {
    HRESULT result;

    {
        Vertex vertices[] = {
            { { -0.7, -0.7 }, { 1.0, 0.0, 0.0 } },
            { {  0.0,  0.7 }, { 0.0, 1.0, 0.0 } },
            { {  0.7, -0.7 }, { 0.0, 0.0, 1.0 } },
        };

        auto properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        auto desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices));
        result = device_->CreateCommittedResource(&properties, D3D12_HEAP_FLAG_NONE, &desc,
            D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&vertex_buffer_));
        assert(SUCCEEDED(result));

        void* data;
        vertex_buffer_->Map(0, nullptr, &data);
        memcpy(data, vertices, sizeof(vertices));

        vertex_buffer_view_.BufferLocation = vertex_buffer_->GetGPUVirtualAddress();
        vertex_buffer_view_.StrideInBytes = sizeof(Vertex);
        vertex_buffer_view_.SizeInBytes = sizeof(vertices);
    }

    {
        uint16_t indices[] = { 0, 1, 2 };

        auto properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        auto desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(indices));
        result = device_->CreateCommittedResource(&properties, D3D12_HEAP_FLAG_NONE, &desc,
            D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&index_buffer_));
        assert(SUCCEEDED(result));

        void* data;
        index_buffer_->Map(0, nullptr, &data);
        memcpy(data, indices, sizeof(indices));

        index_buffer_view_.BufferLocation = index_buffer_->GetGPUVirtualAddress();
        index_buffer_view_.SizeInBytes = sizeof(indices);
        index_buffer_view_.Format = DXGI_FORMAT_R16_UINT;
    }

    {
        ComPtr<ID3DBlob> vertex_code;
        result = CompileShader(L"../../demo/triangle.hlsl", nullptr, "VS", "vs_5_0", &vertex_code);
        assert(SUCCEEDED(result));

        ComPtr<ID3DBlob> pixel_code;
        result = CompileShader(L"../../demo/triangle.hlsl", nullptr, "PS", "ps_5_0", &pixel_code);
        assert(SUCCEEDED(result));

        D3D12_INPUT_ELEMENT_DESC input_element_descs[2] = {
            { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
            { "COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 8, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
        };

        D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {
            .VS = {
                .pShaderBytecode = vertex_code->GetBufferPointer(),
                .BytecodeLength = vertex_code->GetBufferSize()
            },
            .PS = {
                .pShaderBytecode = pixel_code->GetBufferPointer(),
                .BytecodeLength = pixel_code->GetBufferSize()
            },
            .BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT),
            .SampleMask = UINT_MAX,
            .RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT),
            .DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT),
            .InputLayout = {
                .pInputElementDescs = input_element_descs,
                .NumElements = 2
            },
            .PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
            .NumRenderTargets = 1,
            .RTVFormats = {
                kBackBufferFormat
            },
            .DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT,
            .SampleDesc = {
                .Count = 1,
                .Quality = 0
            }
        };

        result = device_->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&pipeline_state_));
        assert(SUCCEEDED(result));
    }
}

//----------------------------------------------------------------------------------------------------------------------

void TriangleApp::OnRender(double delta_time) {
    HRESULT result = S_OK;

    result = command_allocator_->Reset();
    assert(SUCCEEDED(result));

    result = command_list_->Reset(command_allocator_.Get(), nullptr);
    assert(SUCCEEDED(result));

    {
        auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
            GetCurrentBackBuffer(),
            D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

        command_list_->ResourceBarrier(1, &barrier);
    }

    command_list_->RSSetViewports(1, &window_viewport_);
    command_list_->RSSetScissorRects(1, &window_scissor_rect_);

    auto back_buffer_view = GetCurrentBackBuferView();
    auto depth_stencil_view = GetDepthStencilView();

    FLOAT clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    command_list_->ClearRenderTargetView(back_buffer_view, clear_color, 0, nullptr);
    command_list_->ClearDepthStencilView(depth_stencil_view,
        D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
    command_list_->OMSetRenderTargets(1, &back_buffer_view, true, &depth_stencil_view);
    command_list_->SetPipelineState(pipeline_state_.Get());
    command_list_->IASetVertexBuffers(0, 1, &vertex_buffer_view_);
    command_list_->IASetIndexBuffer(&index_buffer_view_);
    command_list_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    command_list_->DrawIndexedInstanced(3, 1, 0, 0, 0);

    {
        auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
            GetCurrentBackBuffer(),
            D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

        command_list_->ResourceBarrier(1, &barrier);
    }

    result = command_list_->Close();
    assert(SUCCEEDED(result));

    ID3D12CommandList* command_lists[] = { command_list_.Get() };
    command_queue_->ExecuteCommandLists(_countof(command_lists), command_lists);

    result = swap_chain_->Present(0, 0);
    assert(SUCCEEDED(result));

    back_buffer_index_ = ++back_buffer_index_ % kBackBufferCount;
    FlushCommandQueue();
}

//----------------------------------------------------------------------------------------------------------------------
