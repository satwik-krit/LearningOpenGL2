#include <iostream>
#include <cmath>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

//#include "Util.h"
#include "Shader.h"

int main(void)
{
    float vertices[] = { 
         //  positions           colors
         0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.0f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
    };
    // float vertices[] = { 
    //      0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    //      0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
    //     -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f 
    // };

    // unsigned int indices[] = { 
    //     0, 1, 2,
    //     0, 3, 2 
    // };

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW.\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "LearningOpenGL2", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (version == 0) 
    {
        std::cout << "Failed to create window.\n";
        glfwTerminate();
        return -1; 
    }

    std::cout << glGetString(GL_VERSION) << '\n';
    
    Shader shader("res/shaders/vert_shader.glsl", "res/shaders/frag_shader.glsl");
    std::cout << shader.id;
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // float timeValue, redValue;
    // int vertexColorLoc = glGetUniformLocation(shaderProgram, "uColor");


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // timeValue = (float)glfwGetTime();
        // redValue = sin(timeValue) / 1.1f + 0.5f;
        // glUniform4f(vertexColorLoc, redValue, 0.0f, 0.0f, 1.0f);
        shader.use();
        glBindVertexArray(VAO);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
