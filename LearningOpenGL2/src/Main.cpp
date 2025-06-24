#include <iostream>
#include <cmath>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

#include "Shader.h"
#include "Util.h"

glm::vec3 light_pos(1.0f, 1.0f, 2.0f);

int main(void)
{

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    
    glm::vec3 cube_positions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int indices[] = { 
        0, 1, 2,
        0, 3, 2 
    };

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW.\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, true);
    // Use OpenGL's debug context
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

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

    // Start using OpenGL's debug context by setting a callback
    glEnable(GL_DEBUG_OUTPUT);
    //glDebugMessageCallback(gl_message_callback, (void*)0);

    std::cout << glGetString(GL_VERSION) << '\n';

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, light_pos);
    model = glm::scale(model, glm::vec3(0.2f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 640.0f/480.0f, 0.1f, 100.0f);
    

    glm::vec3 camera_pos   = glm::vec3(0.0f, 0.0f, 6.0f);
    glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    /* Setting the target to pos+front ensures that the camera keeps looking at 
       the target direction. */
    glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);

    const float radius = 5.0f;
    float cam_x = sin(glfwGetTime()) * radius;
    float cam_z = cos(glfwGetTime()) * radius;

    Shader obj_shader {"res/shaders/object.vert", "res/shaders/object.frag"};
    Shader lamp_shader {"res/shaders/lamp.vert", "res/shaders/lamp.frag"};
    obj_shader.use();
    //obj_shader.set("object_color", 1.0f, 0.5f, 0.31f);
//    obj_shader.set("light_color", 1.0f, 1.0f, 1.0f);

    // TODO: Handle loading of textures in a better way.
    int width, height, nr_channels;
    unsigned char* data;
    stbi_set_flip_vertically_on_load(true);
    
    uint diffuse_map, specular_map;
    glGenTextures(1, &diffuse_map);
    glBindTexture(GL_TEXTURE_2D, diffuse_map);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("res/textures/container.png", &width, &height, &nr_channels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << nr_channels;
    }
    else
    {
        std::cout << "Failed to load texture\n"; 
    }

    stbi_image_free(data);

    glGenTextures(1, &specular_map);
    glBindTexture(GL_TEXTURE_2D, specular_map);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("res/textures/container_specular.png", &width, &height, &nr_channels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << nr_channels;
    }
    else
    {
        std::cout << "Failed to load texture\n"; 
    }

    stbi_image_free(data);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    unsigned int objVAO, lightVAO;
    glGenVertexArrays(1, &objVAO);
    glGenVertexArrays(1, &lightVAO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glBindVertexArray(objVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    glEnable(GL_DEPTH_TEST);
    float current_frame, delta_time = 0.0f, last_frame = 0.0f;
    float camera_speed;
    glm::vec3 light_color, ambientColor, diffuseColor;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // process_input(window);
        current_frame = (float)glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        camera_speed = (10.0f * delta_time);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        { glfwSetWindowShouldClose(window, GLFW_TRUE); }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        { camera_pos += camera_speed * camera_front; }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        { camera_pos -= camera_speed * camera_front; }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        { camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed; }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        { camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed; }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
    }
        // timeValue = (float)glfwGetTime();
        // redValue = sin(timeValue) / 1.1f + 0.5f;
        // glUniform4f(vertexColorLoc, redValue, 0.0f, 0.0f, 1.0f);
        obj_shader.use();

      
        view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);

        obj_shader.set("projection", projection);
        obj_shader.set("view", view);
        obj_shader.set("model", glm::mat4(1.0f));
 
        obj_shader.set("light.ambient", 0.2f, 0.2f, 0.2f);
        obj_shader.set("light.diffuse", 0.5f, 0.5f, 0.5f);
        obj_shader.set("light.specular", 1.0f, 1.0f, 1.0f);
        obj_shader.set("light.position", light_pos);
        obj_shader.set("light.constant", 1.0f);
        obj_shader.set("light.linear", 0.22f);
        obj_shader.set("light.quadratic", 0.2f);
        obj_shader.set("view_pos", camera_pos);

        // obj_shader.set("material.ambient", 1.0f, 0.5f, 0.31f);
        obj_shader.set("material.shininess", 2.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse_map);
        obj_shader.set("material.diffuse", 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_map);
        obj_shader.set("material.specular", 1);

        for (size_t i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cube_positions[i]);
            model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
            obj_shader.set("model", model);
            glBindVertexArray(objVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        lamp_shader.use();
        lamp_shader.set("projection", projection);
        lamp_shader.set("view", view);
        lamp_shader.set("model", model);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
