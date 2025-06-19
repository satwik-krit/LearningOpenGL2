#version 460 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light 
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 normal;
in vec3 frag_pos;

out vec4 frag_color;

uniform Material material;
uniform Light light;

uniform vec3 obj_color;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main() 
{
    vec3 ambient = light.ambient * material.ambient;

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(light_dir, norm), 0.0f);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    float specular_strength = 0.5f;
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    frag_color = vec4(result, 1.0f);
}
