#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "glad/include/glad/glad.h"
#include "glfw/include/GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "VideoPlayer.h"
#include "RoadDetection.h"

class Application {
public:
    GLFWwindow* window{};
    const unsigned int SCR_WIDTH = 1920;
    const unsigned int SCR_HEIGHT = 1080;

    Application();

    void runApp();
};
