#include "Types.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>

#include "Util.hpp"
#include "Camera.hpp"

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

uint texture_from_file(std::string_view filename, std::string_view directory)
{
    std::string path;
    path += directory;
    path += '/';
    path += filename;


    stbi_set_flip_vertically_on_load(true);
    int width, height, nr_channels;
    unsigned char* data = 
        stbi_load(path.c_str(), &width, &height, &nr_channels, 0);

    if (!data) {
        std::cout << "Failed to load texture at path: " << path << '\n';
        stbi_image_free(data);
        return -1;
    }

    GLenum format;
    switch(nr_channels) { 
        case 1: format = GL_RED; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
    }

    uint texture_id;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    return texture_id;
}

void mouse_callback(GLFWwindow* window, double _xpos, double _ypos)
{
    // See if this is the first time we recieved mouse input,
    // not handling it properly causes a sudden jump in the camera.
    static bool first_call = true;
    static float lastx, lasty;
    float xpos = static_cast<float>(_xpos);
    float ypos = static_cast<float>(_ypos);
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (first_call)
    {
        lastx = xpos;
        lasty = ypos;
        first_call = false;
        camera->process_mouse_movement(0.0f, 0.0f);
        return;
    }

    float xoffset = xpos - lastx;
    float yoffset = lasty - ypos; // Flip y because y increases as we move up.

    lastx = xpos;
    lasty = ypos;

    camera->process_mouse_movement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    camera->process_mouse_scroll(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
