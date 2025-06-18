#include <string>
#include <string_view>

#include "GLFW/glfw3.h"

#include "Types.h"

std::string read_file_contents(std::string_view file_path);

// void process_input(GLFWwindow *window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
