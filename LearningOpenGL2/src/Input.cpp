#include "Types.hpp"

#include <GLFW/glfw3.h>

#include "Input.hpp"

void Input::update()
{
    ;
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << key << std::endl;
    if (action == GLFW_PRESS) keys[key] = true;
    else if (action == GLFW_RELEASE) keys[key] = false;
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS) mouse_buttons[button] = true;
    if (action == GLFW_RELEASE) mouse_buttons[button] = false;
}
