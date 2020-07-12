//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#ifndef DX12_DEMO_CLEAR_RTV_APP_H_
#define DX12_DEMO_CLEAR_RTV_APP_H_

#include "app.h"

//----------------------------------------------------------------------------------------------------------------------

class ClearRTVApp : public App {
public:
    ClearRTVApp(GLFWwindow* window);

    void OnRender(double delta_time) override;
};

//----------------------------------------------------------------------------------------------------------------------

#endif // DX12_DEMO_CLEAR_RTV_APP_H_
