#version 460 core

in vec2 tex_coord;

out vec4 frag_color;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() 
{
    frag_color = mix(texture(tex1, tex_coord), 
                     texture(tex2, tex_coord),
                     0.2); 
}
