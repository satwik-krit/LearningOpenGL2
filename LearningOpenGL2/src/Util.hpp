#include "Types.hpp"

#include <GLFW/glfw3.h>

#include <assimp/scene.h>

#include "Mesh.hpp"

std::string read_file_contents(std::string_view file_path);

// void process_input(GLFWwindow *window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void window_resize_callback(GLFWwindow* window, int width, int height);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

uint texture_from_file(std::string_view filename, std::string_view directory);
// uint generate_texture(std::string_view path, 

//void gl_message_callback;
