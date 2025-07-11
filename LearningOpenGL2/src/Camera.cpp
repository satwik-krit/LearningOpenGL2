#include "Types.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"

Camera::Camera(glm::vec3 _position, glm::vec3 _world_up, glm::vec3 _front,
               float _movement_speed, float _mouse_sensitivity)
    : position(_position),
    world_up(_world_up),
    front(_front),
    movement_speed(_movement_speed),
    mouse_sensitivity(_mouse_sensitivity),
    // Set a default value for these, they are going to change every frame anyway.
    yaw(DEFAULT_YAW),
    pitch(DEFAULT_PITCH),
    fov(DEFAULT_FOV)
{
    update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::update_camera_vectors()
{
    glm::vec3 _front;
    float ryaw = glm::radians(yaw), 
          rpitch = glm::radians(pitch); 
    // yaw and pitch in radians
    _front.x = cos(ryaw) * cos(rpitch);
    _front.y = sin(rpitch);
    _front.z = sin(ryaw) * cos(rpitch);
    front = glm::normalize(_front);

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::process_mouse_movement(float xoffset, float yoffset)
{
    yaw += xoffset * mouse_sensitivity;
    pitch += yoffset * mouse_sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    else if (pitch < -89.0f) pitch = -89.0f;

    update_camera_vectors();
}

void Camera::process_mouse_scroll(double xoffset, double yoffset)
{
    fov -= (float)(yoffset);

    if (fov < 1.0f) fov = 1.0f;
    else if (fov > 45.0f) fov = 45.0f;
}
void Camera::process_keyboard_input(float xoffset, float yoffset)
{
    ;
}
