//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_DEMO_TRIANGLE_APP_H_
#define DX12_DEMO_TRIANGLE_APP_H_

#include "app.h"

//----------------------------------------------------------------------------------------------------------------------

class TriangleApp : public App {
public:
    TriangleApp(GLFWwindow* window);

    void OnRender(double delta_time) override;

private:
    ComPtr<ID3D12Resource> vertex_buffer_;
    D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view_;
    ComPtr<ID3D12PipelineState> pipeline_state_;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_DEMO_TRIANGLE_APP_H_

