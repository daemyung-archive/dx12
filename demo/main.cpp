//
// This file is part of the "dx12" project
// See "LICENSE" for license information.
//

#include <memory>
#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>
#include <dxgi.h>
#include <d3d12.h>
#include "clear_rtv_app.h"

//----------------------------------------------------------------------------------------------------------------------

static void OnError(int error, const char* message) {
    spdlog::error("[{}] {}", error, message);
}

//----------------------------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    glfwSetErrorCallback(OnError);

    if (!glfwInit()) {
      spdlog::error("Fail to initialize GLFW!!!");
      exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    auto window = glfwCreateWindow(512, 512, "DX12 Demo Application", nullptr, nullptr);
    if (!window) {
      spdlog::error("Fail to create GLFWwindow!!!");
      glfwTerminate();
      exit(EXIT_FAILURE);
    }

    std::unique_ptr<App> app;

    app = std::make_unique<ClearRTVApp>(window);

    auto prev_time_stamp = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        auto curr_time_stamp = glfwGetTime();
        auto delta_time = curr_time_stamp - prev_time_stamp;

        app->OnUpdate(delta_time);
        app->OnRender(delta_time);

        prev_time_stamp = curr_time_stamp;

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    exit(EXIT_SUCCESS);
}

//----------------------------------------------------------------------------------------------------------------------
