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

glm::vec3 light_pos(1.0f, 1.0f, 2.0f);

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

    
    Model backpack{ "res/models/backpack/backpack.obj" };

    
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
    float camera_speed;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        { camera_pos = glm::vec3(0.0f, 0.0f, 3.0f); }

      
        view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);

        shader.use();

        shader.set("projection", projection);
        shader.set("view", view);
        shader.set("model", glm::mat4(1.0f));

        backpack.draw(shader);
 
        // obj_shader.set("dir_light.direction", -0.2f, -1.0f, -0.3f);
        // obj_shader.set("dir_light.ambient", 0.05f, 0.05f, 0.05f);
        // obj_shader.set("dir_light.diffuse", 0.4f, 0.4f, 0.4f);
        // obj_shader.set("dir_light.specular", 0.5f, 0.5f, 0.5f);
        //
        // // point light 1
        // obj_shader.set("point_lights[0].position", point_light_positions[0]);
        // obj_shader.set("point_lights[0].ambient", 0.05f, 0.05f, 0.05f);
        // obj_shader.set("point_lights[0].diffuse", 0.8f, 0.8f, 0.8f);
        // obj_shader.set("point_lights[0].specular", 1.0f, 1.0f, 1.0f);
        // obj_shader.set("point_lights[0].constant", 1.0f);
        // obj_shader.set("point_lights[0].linear", 0.09f);
        // obj_shader.set("point_lights[0].quadratic", 0.032f);
        //
        // // point light 2
        // obj_shader.set("point_lights[1].position", point_light_positions[1]);
        // obj_shader.set("point_lights[1].ambient", 0.05f, 0.05f, 0.05f);
        // obj_shader.set("point_lights[1].diffuse", 0.8f, 0.8f, 0.8f);
        // obj_shader.set("point_lights[1].specular", 1.0f, 1.0f, 1.0f);
        // obj_shader.set("point_lights[1].constant", 1.0f);
        // obj_shader.set("point_lights[1].linear", 0.09f);
        // obj_shader.set("point_lights[1].quadratic", 0.032f);
        //
        // // point light 3
        // obj_shader.set("point_lights[2].position", point_light_positions[2]);
        // obj_shader.set("point_lights[2].ambient", 0.05f, 0.05f, 0.05f);
        // obj_shader.set("point_lights[2].diffuse", 0.8f, 0.8f, 0.8f);
        // obj_shader.set("point_lights[2].specular", 1.0f, 1.0f, 1.0f);
        // obj_shader.set("point_lights[2].constant", 1.0f);
        // obj_shader.set("point_lights[2].linear", 0.09f);
        // obj_shader.set("point_lights[2].quadratic", 0.032f);
        //
        // // point light 4
        // obj_shader.set("point_lights[3].position", point_light_positions[3]);
        // obj_shader.set("point_lights[3].ambient", 0.05f, 0.05f, 0.05f);
        // obj_shader.set("point_lights[3].diffuse", 0.8f, 0.8f, 0.8f);
        // obj_shader.set("point_lights[3].specular", 1.0f, 1.0f, 1.0f);
        // obj_shader.set("point_lights[3].constant", 1.0f);
        // obj_shader.set("point_lights[3].linear", 0.09f);
        // obj_shader.set("point_lights[3].quadratic", 0.032f);
        //
        // obj_shader.set("spot_light.position", camera_pos);
        // obj_shader.set("spot_light.direction", camera_front);
        // obj_shader.set("spot_light.cutoff", glm::cos(glm::radians(12.5f)));
        // obj_shader.set("spot_light.outer_cutoff", glm::cos(glm::radians(17.5f)));
        // obj_shader.set("spot_light.constant", 1.0f);
        // obj_shader.set("spot_light.linear", 0.09f);
        // obj_shader.set("spot_light.quadratic", 0.032f);
        // obj_shader.set("spot_light.ambient", 0.05f, 0.05f, 0.05f);
        // obj_shader.set("spot_light.diffuse", 0.8f, 0.8f, 0.8f);
        // obj_shader.set("spot_light.specular", 1.0f, 1.0f, 1.0f);
        //
        // obj_shader.set("view_pos", camera_pos);
        //
        // obj_shader.set("material.shininess", 2.0f);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, diffuse_map);
        // obj_shader.set("material.diffuse", 0);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, specular_map);
        // obj_shader.set("material.specular", 1);
        //

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
