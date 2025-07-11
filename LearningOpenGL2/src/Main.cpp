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
#include "Renderer.hpp"

glm::vec3 light_pos(0.0f, 0.0f, 0.0f);

int main(void)
{
    glm::vec3 point_light_positions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    renderer_config config;
    config.win_width = 1024;
    config.win_height = 800;
    config.win_title = "LearningOpenGL";
    config.cam_front = glm::vec3(0.0f, 0.0f, 1.0f);
    config.cam_position = glm::vec3(1.0f, 1.0f, 0.0f);
    config.cam_world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    config.cam_mouse_sensitivity = 0.07f;
    config.cam_movement_speed = 2.5f;
    Renderer renderer{ config };
    Camera& camera = renderer.camera;
    Window& window = renderer.window;
    renderer.init();
    glfwSetWindowUserPointer(renderer.window.glfw_window, static_cast<void*>(&renderer));
    
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

    while (!glfwWindowShouldClose(window.glfw_window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        current_frame = (float)glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        camera.movement_speed = (10.0f * delta_time);

        renderer.process_mouse_input();
        renderer.process_keyboard_input();

        view = camera.get_view_matrix();
        // TODO: Maintain a global screen width and height.
        int w,h;
        glfwGetFramebufferSize(window.glfw_window, &w, &h);
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

        glfwSwapBuffers(window.glfw_window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
