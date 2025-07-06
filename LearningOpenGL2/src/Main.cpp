#include "Types.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.hpp"
#include "Util.hpp"
#include "Model.hpp"
#include "Camera.hpp"

glm::vec3 light_pos(0.0f, 0.0f, 0.0f);

int main(void)
{
    glm::vec3 point_light_positions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (version == 0) 
    {
        std::cout << "Failed to create window.\n";
        glfwTerminate();
        return -1; 
    }

    // Enable OpenGL's debug context and set a callback
    glEnable(GL_DEBUG_OUTPUT);
    //glDebugMessageCallback(gl_message_callback, (void*)0);
    //
    std::cout << glGetString(GL_VERSION) << '\n';

    Camera camera{ CameraAttributes{
        Camera::DEFAULT_POSITION,
        Camera::DEFAULT_WORLD_UP,
        Camera::DEFAULT_FRONT,

        Camera::DEFAULT_MOVEMENT_SPEED,
        Camera::DEFAULT_MOUSE_SENSITIVITY,
        Camera::DEFAULT_ZOOM,
        Camera::DEFAULT_YAW,
        Camera::DEFAULT_PITCH,
    } };
    glfwSetWindowUserPointer(window, static_cast<void*>(&camera));
    
    Model backpack{ "res/models/backpack/backpack.obj" };
    
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, light_pos);
    model = glm::scale(model, glm::vec3(0.2f));
    glm::mat4 projection;
    
    /* Setting the target to pos+front ensures that the camera keeps looking at 
       the target direction. */
    glm::mat4 view;

    Shader shader{ "res/shaders/backpack.vert", "res/shaders/backpack.frag" };
    // Shader lamp_shader{ "res/shaders/backpack.vert", "res/shaders/lamp.frag" };
    
    // unsigned int VBO;
    // glGenBuffers(1, &VBO);
    //
    // unsigned int objVAO, lightVAO;
    // glGenVertexArrays(1, &objVAO);
    // glGenVertexArrays(1, &lightVAO);
    //
    // glBindVertexArray(lightVAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //

    glEnable(GL_DEPTH_TEST);
    float current_frame, delta_time = 0.0f, last_frame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        current_frame = (float)glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        camera.movement_speed = (10.0f * delta_time);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        { glfwSetWindowShouldClose(window, GLFW_TRUE); }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        { camera.position += camera.movement_speed * camera.front; }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        { camera.position -= camera.movement_speed * camera.front; }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        { camera.position += glm::normalize(glm::cross(camera.front, camera.up)) * camera.movement_speed; }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        { camera.position -= glm::normalize(glm::cross(camera.front, camera.up)) * camera.movement_speed; }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        { camera.position = glm::vec3(0.0f, 0.0f, 3.0f); }

      
        view = camera.get_view_matrix();
        // TODO: Maintain a global screen width and height.
        int w,h;
        glfwGetFramebufferSize(window, &w, &h);
        projection = glm::perspective(glm::radians(camera.fov), (float)(w/h), 0.1f, 100.0f);

        shader.use();

        shader.set("projection", projection);
        shader.set("view", view);
        shader.set("model", glm::mat4(1.0f));

 
        shader.set("dir_light.direction", -0.2f, -1.0f, -0.3f);
        shader.set("dir_light.ambient", 0.05f, 0.05f, 0.05f);
        shader.set("dir_light.diffuse", 0.4f, 0.4f, 0.4f);
        shader.set("dir_light.specular", 0.5f, 0.5f, 0.5f);

        // point light 1
        shader.set("point_lights[0].position", point_light_positions[0]);
        shader.set("point_lights[0].ambient", 0.05f, 0.05f, 0.05f);
        shader.set("point_lights[0].diffuse", 0.8f, 0.8f, 0.8f);
        shader.set("point_lights[0].specular", 1.0f, 1.0f, 1.0f);
        shader.set("point_lights[0].constant", 1.0f);
        shader.set("point_lights[0].linear", 0.09f);
        shader.set("point_lights[0].quadratic", 0.032f);

        // point light 2
        shader.set("point_lights[1].position", point_light_positions[1]);
        shader.set("point_lights[1].ambient", 0.05f, 0.05f, 0.05f);
        shader.set("point_lights[1].diffuse", 0.8f, 0.8f, 0.8f);
        shader.set("point_lights[1].specular", 1.0f, 1.0f, 1.0f);
        shader.set("point_lights[1].constant", 1.0f);
        shader.set("point_lights[1].linear", 0.09f);
        shader.set("point_lights[1].quadratic", 0.032f);

        // point light 3
        shader.set("point_lights[2].position", point_light_positions[2]);
        shader.set("point_lights[2].ambient", 0.05f, 0.05f, 0.05f);
        shader.set("point_lights[2].diffuse", 0.8f, 0.8f, 0.8f);
        shader.set("point_lights[2].specular", 1.0f, 1.0f, 1.0f);
        shader.set("point_lights[2].constant", 1.0f);
        shader.set("point_lights[2].linear", 0.09f);
        shader.set("point_lights[2].quadratic", 0.032f);

        // point light 4
        shader.set("point_lights[3].position", point_light_positions[3]);
        shader.set("point_lights[3].ambient", 0.05f, 0.05f, 0.05f);
        shader.set("point_lights[3].diffuse", 0.8f, 0.8f, 0.8f);
        shader.set("point_lights[3].specular", 1.0f, 1.0f, 1.0f);
        shader.set("point_lights[3].constant", 1.0f);
        shader.set("point_lights[3].linear", 0.09f);
        shader.set("point_lights[3].quadratic", 0.032f);

        shader.set("spot_light.position", camera.position);
        shader.set("spot_light.direction", camera.front);
        shader.set("spot_light.cutoff", glm::cos(glm::radians(12.5f)));
        shader.set("spot_light.outer_cutoff", glm::cos(glm::radians(17.5f)));
        shader.set("spot_light.constant", 1.0f);
        shader.set("spot_light.linear", 0.09f);
        shader.set("spot_light.quadratic", 0.032f);
        shader.set("spot_light.ambient", 0.05f, 0.05f, 0.05f);
        shader.set("spot_light.diffuse", 0.8f, 0.8f, 0.8f);
        shader.set("spot_light.specular", 1.0f, 1.0f, 1.0f);

        shader.set("view_pos", camera.position);

        shader.set("material.shininess", 2.0f);
        shader.set("material.diffuse", 0);
        shader.set("material.specular", 1);

        backpack.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
