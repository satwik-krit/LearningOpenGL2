#include "Types.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"

Camera::Camera(CameraAttributes _attrs) : position(_attrs.position),
                                          world_up(_attrs.world_up),
                                          front(_attrs.front),
                                          movement_speed(_attrs.movement_speed),
                                          mouse_sensitivity(_attrs.mouse_sensitivity),
                                          zoom(_attrs.zoom),
                                          yaw(_attrs.yaw),
                                          pitch(_attrs.pitch)
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
    pitch += xoffset * mouse_sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    else if (pitch < -89.0f) pitch = -89.0f;

    update_camera_vectors();
}

void Camera::process_mouse_scroll(double xoffset, double yoffset)
{
    fov -= (float)(-yoffset);

    if (fov < 1.0f) fov = 1.0f;
    else if (fov > 45.0f) fov = 45.0f;
}
void process_keyboard_input(float xoffset, float yoffset)
{
    ;
}
