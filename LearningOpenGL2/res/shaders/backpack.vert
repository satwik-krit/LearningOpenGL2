#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_tex_coords;

out vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    tex_coords = in_tex_coords;
    gl_Position = projection * view * vec4(pos, 1.0f);
}
