#include <fstream>
#include <string>
#include <iostream>
#include <string_view>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "Util.h"
#include "Types.h"

std::string read_file_contents(std::string_view file_path)
{
    std::string line;
    std::ifstream file(file_path.data());
    std::stringstream sstream;

    if (file.is_open())
    {
        sstream << file.rdbuf();
        // if (!file.eof())
        // {
        //     std::cout << "ERROR::FILE\n" << "Did not reach EOF: " << file_path << '\n';
        // }

        file.close();
        return sstream.str();
    } 

    std::cout << "ERROR::FILE\n" << "Failed to open file " << file_path << '\n';
    return "";
}

/*void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        { glfwSetWindowShouldClose(window, GLFW_TRUE); }

    const float camera_speed = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        { camera_pos += camera_speed * camera_front; }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        { camera_pos -= camera_speed * camera_front; }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        { camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed; }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        { camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed; }
}
*/
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}
