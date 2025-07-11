#include "Types.hpp"

#include <glad/glad.h>

#include "Window.hpp"
#include "Util.hpp"

Window::Window(uint _width, uint _height, std::string_view _title)
    : width(_width),
    height(_height),
    title(_title),
    // glfw_window is a nullptr since it is initialised in Window.init()
    glfw_window(nullptr)
{ ; }

bool Window::init()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW.\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, true);
    // Use OpenGL's debug context
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    glfw_window = glfwCreateWindow(width, height, title.data(), NULL, NULL);
    if (!glfw_window)
    {
        std::cout << "Failed to create window.\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(glfw_window);
    glfwSetCursorPosCallback(glfw_window, mouse_callback);
    glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
    glfwSetScrollCallback(glfw_window, scroll_callback);
    glfwSetMouseButtonCallback(glfw_window, mouse_button_callback);
    glfwSetKeyCallback(glfw_window, key_callback);
    glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (version == 0) 
    {
        std::cout << "Failed to create window.\n";
        glfwTerminate();
        return false; 
    }

    // Enable OpenGL's debug context and set a callback
    glEnable(GL_DEBUG_OUTPUT);
    //glDebugMessageCallback(gl_message_callback, (void*)0);
    std::cout << glGetString(GL_VERSION) << std::endl;
    return true;
}
