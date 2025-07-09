#pragma once

#include "Types.hpp"

#include <GLFW/glfw3.h>

/* Store the state of keys (affected by when they are pressed and released),
 * mouse buttons, and coordinates of the cursor in the window.
 *
 * As of now, we are only concerned with left, right and middle mouse buttons.
 */

class Input {
public:
    std::unordered_map<uint, bool> keys{ false };
    std::unordered_map<uint, bool> mouse_buttons{ false };
    float mouse_x, mouse_y;
public:
    void update();
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};
