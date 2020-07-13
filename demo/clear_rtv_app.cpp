//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include "clear_rtv_app.h"

#include <cassert>

//----------------------------------------------------------------------------------------------------------------------

ClearRTVApp::ClearRTVApp(GLFWwindow* window)
: App(window) {
}

//----------------------------------------------------------------------------------------------------------------------

void ClearRTVApp::OnRender(double delta_time) {
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

    FLOAT clear_color[4] = { 0.2f, 0.2f, 0.8f, 1.0f };
    command_list_->ClearRenderTargetView(back_buffer_view, clear_color, 0, nullptr);
    command_list_->OMSetRenderTargets(1, &back_buffer_view, true, nullptr);

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
