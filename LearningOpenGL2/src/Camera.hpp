#pragma once

#include "Types.hpp"

#include <glm/glm.hpp>

#include "Input.hpp"

static const float DEFAULT_YAW = -90.0f;
static const float DEFAULT_PITCH = 0;
static const float DEFAULT_FOV = 45.0f;

static const float DEFAULT_MOVEMENT_SPEED = 2.5f;
static const float DEFAULT_MOUSE_SENSITIVITY = 0.07f;
static const float DEFAULT_ZOOM = 45.0f;

static const glm::vec3 DEFAULT_WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
static const glm::vec3 DEFAULT_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
static const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    glm::vec3 position;
    glm::vec3 world_up;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    float movement_speed;
    float mouse_sensitivity;

    // Euler angles
    float yaw;
    float pitch;

    float fov;

public:
    Camera(glm::vec3 position, glm::vec3 world_up, glm::vec3 front,
           float movement_speed, float mouse_sensitivity);
    glm::mat4 get_view_matrix();
    void process_mouse_movement(const Input& input);
    void process_mouse_scroll(const Input& input);
    void process_keyboard_input(Input& input);

private:
    void update_camera_vectors();
};
