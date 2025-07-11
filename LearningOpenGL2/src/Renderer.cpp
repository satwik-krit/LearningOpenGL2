#include "Types.hpp"

#include "Camera.hpp"
#include "Renderer.hpp"

Renderer::Renderer(renderer_config config)
    : window(config.win_width, config.win_height, config.win_title),
    camera(config.cam_position, config.cam_world_up, config.cam_front,
           config.cam_movement_speed, config.cam_mouse_sensitivity)
{
	;
}

bool Renderer::init()
{
    window.init();
    return true;
}

void Renderer::process_mouse_input()
{
    camera.process_mouse_movement(input);
    camera.process_mouse_scroll(input);
}

void Renderer::process_keyboard_input()
{
    camera.process_keyboard_input(input);
}
