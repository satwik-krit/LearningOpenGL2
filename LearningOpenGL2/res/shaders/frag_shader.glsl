#version 460 core

in vec3 uColor;

out vec4 FragColor;

void main() 
{
    FragColor = vec4(uColor, 1.0f); 
}
