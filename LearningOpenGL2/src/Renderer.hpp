#pragma once

#include "Types.hpp"

#include <glm/glm.hpp>

#include "Camera.hpp"
#include "Input.hpp"
#include "Util.hpp"
#include "Window.hpp"
#include "Model.hpp"

struct renderer_config {
    // Window
    uint win_width;
    uint win_height;
    std::string_view win_title;
    
    // Camera
    glm::vec3 cam_position;
    glm::vec3 cam_world_up;
    glm::vec3 cam_front;
    float cam_movement_speed;
    float cam_mouse_sensitivity;
};

class Renderer {
public:
    Camera camera;
    Input input;
    Window window;
    std::vector<Model*> models;
private:
public:
    Renderer(renderer_config config);
    bool init();
    void process_mouse_input();
    void process_keyboard_input();
};
