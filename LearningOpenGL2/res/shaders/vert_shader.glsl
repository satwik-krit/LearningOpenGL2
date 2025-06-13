#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 in_tex_coord;

out vec3 u_color;
out vec2 tex_coord;

uniform mat4 transform;

void main() 
{
    gl_Position = transform * vec4(pos, 1.0f);
    u_color = color; 
    tex_coord = in_tex_coord;
}

