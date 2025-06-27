#include "Types.hpp"

#include <GLFW/glfw3.h>

#include <assimp/scene.h>

#include "Mesh.hpp"

std::string read_file_contents(std::string_view file_path);

// void process_input(GLFWwindow *window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

uint texture_from_file(std::string_view filename, std::string_view directory);
// uint generate_texture(std::string_view path, 

//void gl_message_callback;
