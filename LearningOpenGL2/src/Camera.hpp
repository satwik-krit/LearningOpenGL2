#pragma once

#include "Types.hpp"

#include <glm/glm.hpp>

static const float DEFAULT_YAW;
static const float DEFAULT_PITCH;

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

struct CameraAttributes {
    glm::vec3 position;
    glm::vec3 world_up;
    glm::vec3 front;

    float movement_speed;
    float mouse_sensitivity;
    float zoom;

    // Euler angles
    float yaw;
    float pitch;
};

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 world_up;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    float movement_speed;
    float mouse_sensitivity;
    float zoom;

    // Euler angles
    float yaw;
    float pitch;

    inline static const float DEFAULT_YAW = -90.0f;
    inline static const float DEFAULT_PITCH = 0;

    inline static const float DEFAULT_MOVEMENT_SPEED = 2.5f;
    inline static const float DEFAULT_MOUSE_SENSITIVITY = 0.07f;
    inline static const float DEFAULT_ZOOM = 45.0f;

    inline static const glm::vec3 DEFAULT_WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
    inline static const glm::vec3 DEFAULT_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
    inline static const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);

    float fov;

public:
    Camera(CameraAttributes _attrs);
    glm::mat4 get_view_matrix();
    void process_mouse_movement(float xoffset, float yoffset);
    void process_mouse_scroll(double xoffset, double yoffset);
    void process_keyboard_input(float xoffset, float yoffset);

private:
    void update_camera_vectors();
};
