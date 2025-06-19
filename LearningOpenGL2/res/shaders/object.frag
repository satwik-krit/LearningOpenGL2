#version 460 core

in vec3 normal;
in vec3 frag_pos;

out vec4 frag_color;

uniform vec3 obj_color;
uniform vec3 light_color;
uniform vec3 light_pos;

void main() 
{
    float ambient_strength = 0.1f;
    vec3 ambient = ambient_strength * light_color;

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(light_dir, norm), 0.0f);
    vec3 diffuse = diff * light_color;

    vec3 result = (ambient + diffuse) * obj_color;
    frag_color = vec4(result, 1.0f);
}
