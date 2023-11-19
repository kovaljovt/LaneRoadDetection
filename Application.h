#include <iostream>
#include <string>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>


class Application {
public:
    GLFWwindow* window;

    Application();
    void runApp(GLFWwindow* window);
};