#version 460 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
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
in vec2 tex_coords;

out vec4 frag_color;

uniform Material material;
uniform Light light;
uniform vec3 view_pos;

void main() 
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light.position - frag_pos);
    float diff = max(dot(light_dir, norm), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, tex_coords));

    float specular_strength = 0.5f;
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, tex_coords));

    vec3 result = ambient + diffuse + specular;
    frag_color = vec4(result, 1.0f);
}
