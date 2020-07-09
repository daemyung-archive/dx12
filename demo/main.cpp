//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <cstdlib>
#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <dxgi.h>
#include <d3d12.h>

static void OnError(int error, const char* message) {
    spdlog::error("[{}] {}", error, message);
}

class App {
public:
    App() {
        {
            CreateDXGIFactory(IID_PPV_ARGS(&factory_ptr_));
            assert(factory_ptr_);
        }

        {
            D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device_ptr_));
            assert(device_ptr_);
        }

        {
            D3D12_COMMAND_QUEUE_DESC desc = {
                .Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
                .Flags = D3D12_COMMAND_QUEUE_FLAG_NONE
            };

            device_ptr_->CreateCommandQueue(&desc, IID_PPV_ARGS(&command_queue_ptr_));
            assert(command_queue_ptr_);
        }

        {
            device_ptr_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&command_allocator_ptr_));
            assert(command_allocator_ptr_);
        }

        {
            device_ptr_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator_ptr_, nullptr, IID_PPV_ARGS(&command_list_ptr_));
            assert(command_list_ptr_);

            command_list_ptr_->Close();
        }

        {
            D3D12_DESCRIPTOR_HEAP_DESC desc = {
                .NumDescriptors = 2,
                .Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
                .Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE
            };

            device_ptr_->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&rtv_heap_ptr_));
            assert(rtv_heap_ptr_);

            rtv_descriptor_size_ = device_ptr_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        }
    }

    void Connect(GLFWwindow* window_ptr) {
        DXGI_SWAP_CHAIN_DESC desc = {
            .BufferDesc = {
                .Width = 512,
                .Height = 512,
                .Format = DXGI_FORMAT_B8G8R8A8_UNORM
            },
            .SampleDesc = {
                .Count = 0,
                .Quality = 1
            },
            .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
            .BufferCount = 2,
            .OutputWindow = glfwGetCocoaWindow(window_ptr),
            .Windowed = true,
            .SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
            .Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
        };

        factory_ptr_->CreateSwapChain(command_queue_ptr_, &desc, &swap_chain_ptr_);
        assert(swap_chain_ptr_);

        // D3DResource**
        auto rtv_descriptor_handle = rtv_heap_ptr_->GetCPUDescriptorHandleForHeapStart();
        for (auto i = 0; i != 2; ++ i) {
            swap_chain_ptr_->GetBuffer(i, IID_PPV_ARGS(&swap_chain_buffer_ptrs_[i]));
            device_ptr_->CreateRenderTargetView(swap_chain_buffer_ptrs_[i], nullptr, rtv_descriptor_handle);
            rtv_descriptor_handle.ptr += rtv_descriptor_size_;
        }
    }

    void OnRender(float dalta_time) {
        command_allocator_ptr_->Reset();
        command_list_ptr_->Reset(command_allocator_ptr_, nullptr);

        {
            D3D12_RESOURCE_BARRIER barrier = {
                .Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
                .Transition = {
                    .pResource = swap_chain_buffer_ptrs_[frame_index_],
                    .Subresource = 0,
                    .StateBefore = D3D12_RESOURCE_STATE_PRESENT,
                    .StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET
                }
            };

            command_list_ptr_->ResourceBarrier(1, &barrier);
        }

        command_list_ptr_->RSSetViewports(1, &viewport_);
        command_list_ptr_->RSSetScissorRects(1, &scissor_);

        auto rtv_descriptor_handle = rtv_heap_ptr_->GetCPUDescriptorHandleForHeapStart();
        rtv_descriptor_handle.ptr += frame_index_ * rtv_descriptor_size_;

        static FLOAT clear_color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

        command_list_ptr_->ClearRenderTargetView(rtv_descriptor_handle, clear_color, 0, nullptr);
        command_list_ptr_->OMSetRenderTargets(1, &rtv_descriptor_handle, true, nullptr);

        clear_color[0] += 0.01f;

        if (clear_color[0] > 1.0f)
            clear_color[0] = 0.0f;

        {
            D3D12_RESOURCE_BARRIER barrier = {
                .Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
                .Transition = {
                    .pResource = swap_chain_buffer_ptrs_[frame_index_],
                    .Subresource = 0,
                    .StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET,
                    .StateAfter = D3D12_RESOURCE_STATE_PRESENT
                }
            };

            command_list_ptr_->ResourceBarrier(1, &barrier);
        }

        command_list_ptr_->Close();

        ID3D12CommandList* command_lists[] = { command_list_ptr_ };
        command_queue_ptr_->ExecuteCommandLists(1, command_lists);

        swap_chain_ptr_->Present(0, 0);
        frame_index_ = (frame_index_ + 1) % 2;
    }

private:
    IDXGIFactory* factory_ptr_ = { nullptr };
    ID3D12Device* device_ptr_ = { nullptr };
    ID3D12CommandQueue* command_queue_ptr_ = { nullptr };
    ID3D12CommandAllocator* command_allocator_ptr_ = { nullptr };
    ID3D12GraphicsCommandList* command_list_ptr_ = { nullptr };
    IDXGISwapChain* swap_chain_ptr_ = { nullptr };
    ID3D12DescriptorHeap* rtv_heap_ptr_ = { nullptr };
    UINT rtv_descriptor_size_ = { 0 };
    ID3D12Resource* swap_chain_buffer_ptrs_[2];
    D3D12_VIEWPORT viewport_;
    D3D12_RECT     scissor_;
    UINT frame_index_ = { 0 };
};

int main(int argc, char* argv[])
{
    glfwSetErrorCallback(OnError);

    if (!glfwInit()) {
      spdlog::error("Fail to initialize GLFW!!!");
      exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    auto window_ptr = glfwCreateWindow(512, 512, "DX12 Demo Application", nullptr, nullptr);
    if (!window_ptr) {
      spdlog::error("Fail to create GLFWwindow!!!");
      glfwTerminate();
      exit(EXIT_FAILURE);
    }

    App app;
    app.Connect(window_ptr);

    auto prev_time_stamp = glfwGetTime();
    while (!glfwWindowShouldClose(window_ptr)) {
        auto curr_time_stamp = glfwGetTime();
        app.OnRender(curr_time_stamp - prev_time_stamp);
        prev_time_stamp = curr_time_stamp;

        glfwPollEvents();
    }

    glfwDestroyWindow(window_ptr);
    glfwTerminate();
    
    exit(EXIT_SUCCESS);
}
