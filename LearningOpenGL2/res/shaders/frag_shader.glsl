#version 460 core

in vec3 u_color;
in vec2 tex_coord;

out vec4 frag_color;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() 
{
    frag_color = mix(texture(tex1, tex_coord), texture(tex2, vec2(1.0f - tex_coord.x, tex_coord.y)), 0.5); 
}
