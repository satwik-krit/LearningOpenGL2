#pragma once

#include "Types.hpp"

#include <GLFW/glfw3.h>

/* Store the state of keys (affected by when they are pressed and released),
 * mouse buttons, and coordinates of the cursor in the window.
 *
 * As of now, we are only concerned with left, right and middle mouse buttons.
 */

struct Input {
    std::unordered_map<uint, bool> keys{ false };
    std::unordered_map<uint, bool> mouse_buttons{ false };
    float mouse_x, mouse_y;
    float x_offset, y_offset;
    float scroll_xoffset, scroll_yoffset;
};
