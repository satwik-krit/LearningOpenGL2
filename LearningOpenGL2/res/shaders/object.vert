#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 in_normal;

out vec3 normal;
out vec3 frag_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    frag_pos = vec3(model * vec4(pos, 1.0f));
    normal = in_normal;
}

