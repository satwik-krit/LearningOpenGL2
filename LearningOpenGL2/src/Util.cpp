#include "Types.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>

#include "Util.hpp"
#include "Renderer.hpp"

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

/* GLFW INPUT CALLBACKS
 * These only update the *Input* instance of the renderer with user input.
 * *Input* is then used by every component that relies on user input.
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    switch (action)
    {
        case GLFW_PRESS: { renderer->input.keys[key] = true; break; }
        case GLFW_RELEASE: { renderer->input.keys[key] = false; break; }
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    switch (action)
    {
        case GLFW_PRESS: { renderer->input.mouse_buttons[button] = true; break; }
        case GLFW_RELEASE: { renderer->input.mouse_buttons[button] = false; break; }
    }
}

void mouse_callback(GLFWwindow* window, double _xpos, double _ypos)
{
    // See if this is the first time we recieved mouse input,
    // not handling it properly causes a sudden jump in the camera.
    static bool first_call = true;
    static float lastx, lasty;
    float xpos = static_cast<float>(_xpos);
    float ypos = static_cast<float>(_ypos);
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

    if (first_call)
    {
        lastx = xpos;
        lasty = ypos;
        first_call = false;
        renderer->input.mouse_x = xpos;
        renderer->input.mouse_y = ypos;

        renderer->input.x_offset = 0.0f;
        renderer->input.y_offset = 0.0f;
        return;
    }

    float xoffset = xpos - lastx;
    float yoffset = lasty - ypos; // Flip y because y increases as we move up.

    lastx = xpos;
    lasty = ypos;

    renderer->input.mouse_x = xpos;
    renderer->input.mouse_y = ypos;

    renderer->input.x_offset = xoffset;
    renderer->input.y_offset = yoffset;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    renderer->input.scroll_xoffset = static_cast<float>(xoffset);
    renderer->input.scroll_yoffset = static_cast<float>(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    renderer->window.width = width;
    renderer->window.height = height;
    glViewport(0, 0, width, height);
}
