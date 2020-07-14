//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <iostream>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "app.h"

//----------------------------------------------------------------------------------------------------------------------

App::~App() {
    FlushCommandQueue();
}

//----------------------------------------------------------------------------------------------------------------------

void App::OnUpdate(double delta_time) {
}

//----------------------------------------------------------------------------------------------------------------------

void App::OnRender(double delta_time) {
}

//----------------------------------------------------------------------------------------------------------------------

void App::OnResize() {
    HRESULT result = S_OK;

    FlushCommandQueue();

    result = command_list_->Reset(command_allocator_.Get(), nullptr);
    assert(SUCCEEDED(result));

    int width, height;
    glfwGetWindowSize(window_, &width, &height);

    result = swap_chain_->ResizeBuffers(kBackBufferCount, width, height, kBackBufferFormat,
        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
    assert(SUCCEEDED(result));

    back_buffer_index_ = 0;

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_descriptor(
        descriptor_heaps_[D3D12_DESCRIPTOR_HEAP_TYPE_RTV]->GetCPUDescriptorHandleForHeapStart());

    for (auto i = 0; i != kBackBufferCount; ++i) {
        result = swap_chain_->GetBuffer(i, IID_PPV_ARGS(&back_buffers_[i]));
        assert(SUCCEEDED(result));

        device_->CreateRenderTargetView(back_buffers_[i].Get(), nullptr, rtv_descriptor);
        rtv_descriptor.Offset(1, descriptor_inc_sizes_[D3D12_DESCRIPTOR_HEAP_TYPE_RTV]);
    }

    CD3DX12_HEAP_PROPERTIES heap_properties(D3D12_HEAP_TYPE_DEFAULT);

    D3D12_RESOURCE_DESC depth_stencil_desc = {
        .Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Width = static_cast<UINT64>(width),
        .Height = static_cast<UINT>(height),
        .DepthOrArraySize = 1,
        .MipLevels = 1,
        .Format = DXGI_FORMAT_D24_UNORM_S8_UINT,
        .SampleDesc = {
            .Count = 1,
            .Quality = 0
        },
        .Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
    };

    result = device_->CreateCommittedResource(&heap_properties, D3D12_HEAP_FLAG_NONE,
        &depth_stencil_desc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&depth_stencil_buffer_));
    assert(SUCCEEDED(result));

    D3D12_DEPTH_STENCIL_VIEW_DESC dsv_desc = {
        .Format = DXGI_FORMAT_D24_UNORM_S8_UINT,
        .ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D,
        .Flags = D3D12_DSV_FLAG_NONE,
        .Texture2D = {
            .MipSlice = 0
        }
    };

    device_->CreateDepthStencilView(depth_stencil_buffer_.Get(), &dsv_desc, GetDepthStencilView());

    {
        auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(depth_stencil_buffer_.Get(),
            D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE);

        command_list_->ResourceBarrier(1, &barrier);
    }

    result = command_list_->Close();
    assert(SUCCEEDED(result));

    ID3D12CommandList* command_lists[] = { command_list_.Get() };
    command_queue_->ExecuteCommandLists(_countof(command_lists), command_lists);

    FlushCommandQueue();

    window_viewport_.TopLeftX = 0;
    window_viewport_.TopLeftY = 0;
    window_viewport_.Width = static_cast<float>(width);
    window_viewport_.Height = static_cast<float>(height);
    window_viewport_.MinDepth = 0.0f;
    window_viewport_.MaxDepth = 1.0f;

    window_scissor_rect_.left = 0;
    window_scissor_rect_.top = 0;
    window_scissor_rect_.right = width;
    window_scissor_rect_.bottom = height;
}

//----------------------------------------------------------------------------------------------------------------------

App::App(GLFWwindow* window)
: window_(window) {
    InitD3D12();
    OnResize();
}

//----------------------------------------------------------------------------------------------------------------------

void App::FlushCommandQueue() {
}

//----------------------------------------------------------------------------------------------------------------------

void App::CreateDescriptorHeaps() {
    HRESULT result = S_OK;

    D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc = {
        .Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
        .NumDescriptors = kBackBufferCount,
        .Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE
    };

    result = device_->CreateDescriptorHeap(
        &rtv_heap_desc, IID_PPV_ARGS(&descriptor_heaps_[D3D12_DESCRIPTOR_HEAP_TYPE_RTV]));
    assert(SUCCEEDED(result));

    D3D12_DESCRIPTOR_HEAP_DESC dsv_heap_desc = {
        .Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
        .NumDescriptors = 1,
        .Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE
    };

    result = device_->CreateDescriptorHeap(
        &dsv_heap_desc, IID_PPV_ARGS(&descriptor_heaps_[D3D12_DESCRIPTOR_HEAP_TYPE_DSV]));
    assert(SUCCEEDED(result));
}

//----------------------------------------------------------------------------------------------------------------------

ID3D12Resource* App::GetCurrentBackBuffer() const {
    return back_buffers_[back_buffer_index_].Get();
}

//----------------------------------------------------------------------------------------------------------------------

CD3DX12_CPU_DESCRIPTOR_HANDLE App::GetCurrentBackBuferView() const {
    return CD3DX12_CPU_DESCRIPTOR_HANDLE(
        descriptor_heaps_[D3D12_DESCRIPTOR_HEAP_TYPE_RTV]->GetCPUDescriptorHandleForHeapStart(),
        back_buffer_index_,
        descriptor_inc_sizes_[D3D12_DESCRIPTOR_HEAP_TYPE_RTV]);
}

//----------------------------------------------------------------------------------------------------------------------

CD3DX12_CPU_DESCRIPTOR_HANDLE App::GetDepthStencilView() const {
    return CD3DX12_CPU_DESCRIPTOR_HANDLE(
        descriptor_heaps_[D3D12_DESCRIPTOR_HEAP_TYPE_DSV]->GetCPUDescriptorHandleForHeapStart());
}

//----------------------------------------------------------------------------------------------------------------------

void App::InitD3D12() {
    HRESULT result = S_OK;

    result = CreateDXGIFactory(IID_PPV_ARGS(&factory_));
    assert(SUCCEEDED(result));

    result = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device_));
    assert(SUCCEEDED(result));

    for (auto i = 0; i != D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES; ++i) {
        descriptor_inc_sizes_[i] = device_->GetDescriptorHandleIncrementSize(
            static_cast<D3D12_DESCRIPTOR_HEAP_TYPE>(i));
    }

    CreateDescriptorHeaps();
    CreateCommandObjects();
    CreateSwapChain();
}

//----------------------------------------------------------------------------------------------------------------------

void App::CreateCommandObjects() {
    HRESULT result = S_OK;

    D3D12_COMMAND_QUEUE_DESC queue_desc = {
        .Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
        .Flags = D3D12_COMMAND_QUEUE_FLAG_NONE
    };

    result = device_->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&command_queue_));
    assert(SUCCEEDED(result));

    result = device_->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&command_allocator_));
    assert(SUCCEEDED(result));

    result = device_->CreateCommandList(
        0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator_.Get(), nullptr,
        IID_PPV_ARGS(&command_list_));
    assert(SUCCEEDED(result));

    result = command_list_->Close();
    assert(SUCCEEDED(result));
}

//----------------------------------------------------------------------------------------------------------------------

void App::CreateSwapChain() {
    HRESULT result = S_OK;

    int width, height;
    glfwGetWindowSize(window_, &width, &height);

    DXGI_SWAP_CHAIN_DESC swap_chain_desc = {
        .BufferDesc = {
            .Width = static_cast<UINT>(width),
            .Height = static_cast<UINT>(height),
            .RefreshRate = {
                .Numerator = 60,
                .Denominator = 1
            },
            .Format = kBackBufferFormat,
            .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
            .Scaling = DXGI_MODE_SCALING_UNSPECIFIED
        },
        .SampleDesc = {
            .Count = 1,
            .Quality = 0
        },
        .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
        .BufferCount = kBackBufferCount,
        .OutputWindow = glfwGetCocoaWindow(window_),
        .Windowed = true,
        .SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
        .Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
    };

    result = factory_->CreateSwapChain(command_queue_.Get(), &swap_chain_desc, &swap_chain_);
    assert(SUCCEEDED(result));
}

//----------------------------------------------------------------------------------------------------------------------

HRESULT CompileShader(const std::wstring& file_name, const D3D_SHADER_MACRO* defines,
    const std::string& entrypoint, const std::string& target, ID3DBlob** code) {
    HRESULT result = S_OK;

    ComPtr<ID3DBlob> error;
    result = D3DCompileFromFile(&file_name[0], defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        entrypoint.c_str(), target.c_str(), 0, 0, code, &error);

    if (error != nullptr) {
        std::cerr << static_cast<char*>(error->GetBufferPointer()) << std::endl;
    }

    assert(SUCCEEDED(result));

    return result;
}

//----------------------------------------------------------------------------------------------------------------------
