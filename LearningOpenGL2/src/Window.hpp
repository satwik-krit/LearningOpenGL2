#pragma once

#include "Types.hpp"

#include <GLFW/glfw3.h>

class Window {
public:
    uint width, height;
    std::string_view title;
    GLFWwindow* glfw_window;
public:
    Window(uint _width = 640, uint _height = 640, std::string_view _title = "DefaultTitle");
    bool init();
};
