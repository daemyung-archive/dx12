//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

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

        device_->CreateRenderTargetView(back_buffers_[i], nullptr, rtv_descriptor);
        rtv_descriptor.Offset(1, descriptor_inc_sizes_[D3D12_DESCRIPTOR_HEAP_TYPE_RTV]);
    }

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
    return back_buffers_[back_buffer_index_];
}

//----------------------------------------------------------------------------------------------------------------------

D3D12_CPU_DESCRIPTOR_HANDLE App::GetCurrentBackBuferView() const {
    return CD3DX12_CPU_DESCRIPTOR_HANDLE(
        descriptor_heaps_[D3D12_DESCRIPTOR_HEAP_TYPE_RTV]->GetCPUDescriptorHandleForHeapStart(),
        back_buffer_index_,
        descriptor_inc_sizes_[D3D12_DESCRIPTOR_HEAP_TYPE_RTV]);
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
        0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator_, nullptr,
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

    result = factory_->CreateSwapChain(command_queue_, &swap_chain_desc, &swap_chain_);
    assert(SUCCEEDED(result));
}

//----------------------------------------------------------------------------------------------------------------------
