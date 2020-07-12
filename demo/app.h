//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_DEMO_APP_H_
#define DX12_DEMO_APP_H_

#include <GLFW/glfw3.h>
#include <dxgi.h>
#include <d3d12.h>
#include "d3dx12.h"

//----------------------------------------------------------------------------------------------------------------------

constexpr auto kBackBufferCount = 2;
constexpr auto kBackBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;

//----------------------------------------------------------------------------------------------------------------------

class App {
public:
    virtual ~App();

    virtual void OnUpdate(double delta_time);

    virtual void OnRender(double delta_time);

    virtual void OnResize();

protected:
    App(GLFWwindow* window);

    virtual void CreateDescriptorHeaps();

    void FlushCommandQueue();

    ID3D12Resource* GetCurrentBackBuffer() const;

    D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBuferView() const;

private:
    void InitD3D12();

    void CreateCommandObjects();

    void CreateSwapChain();

protected:
    GLFWwindow* window_ = { nullptr };
    IDXGIFactory* factory_ = { nullptr };
    ID3D12Device* device_ = { nullptr };
    UINT descriptor_inc_sizes_[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
    ID3D12DescriptorHeap* descriptor_heaps_[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
    ID3D12CommandQueue* command_queue_ = { nullptr };
    ID3D12CommandAllocator* command_allocator_ = { nullptr };
    ID3D12GraphicsCommandList* command_list_ = { nullptr };
    IDXGISwapChain* swap_chain_ = { nullptr };
    ID3D12Resource* back_buffers_[kBackBufferCount];
    UINT back_buffer_index_ = { 0 };
    D3D12_VIEWPORT window_viewport_;
    D3D12_RECT window_scissor_rect_;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_DEMO_APP_H_
