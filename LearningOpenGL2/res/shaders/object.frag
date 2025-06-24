#version 460 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight 
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dir_light;

#define NR_POINT_LIGHTS 4
struct PointLight 
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform PointLight point_lights[NR_POINT_LIGHTS];

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutoff;
    float outer_cutoff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spot_light;

struct Light 
{
    vec3 position;
    vec3 direction;
    float cutoff;
    float outer_cutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coords;

out vec4 frag_color;

uniform Material material;
// uniform Light light;
uniform vec3 view_pos;

vec3 calc_dir_light(DirLight light, vec3 normal, vec3 view_dir);
vec3 calc_point_light(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);
vec3 calc_spot_light(SpotLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);

void main() 
{
    vec3 norm = normalize(normal);
    vec3 view_dir = normalize(view_pos - frag_pos);

    // Directional lighting
    vec3 result = calc_dir_light(dir_light, norm, view_dir);

    // Point lighting
    for (int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        result += calc_point_light(point_lights[i], norm, frag_pos, view_dir);
    }

    // Spot lighting
    result += calc_spot_light(spot_light, norm, frag_pos, view_dir);

    frag_color = vec4(result, 1.0f);

    // // Ambient lighting is calculated in both cases.
    // vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));
    // vec3 result = ambient;
    //
    // vec3 light_dir = normalize(light.position - frag_pos);
    // float theta     = dot(light_dir, normalize(-light.direction));
    // float epsilon   = light.cutoff - light.outer_cutoff;
    // float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0f, 1.0f);
    //
    // vec3 norm = normalize(normal);
    // float diff = max(dot(light_dir, norm), 0.0f);
    // vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, tex_coords));
    //
    // float specular_strength = 0.5f;
    // vec3 view_dir = normalize(view_pos - frag_pos);
    // vec3 reflect_dir = reflect(-light_dir, norm);
    // float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shininess);
    // vec3 specular = light.specular * spec * vec3(texture(material.specular, tex_coords));
    //
    // // attenuation
    // float distance    = length(light.position - frag_pos);
    // float attenuation = 1.0 / 
    //     (light.constant +
    //     light.linear * distance +
    //     light.quadratic * (distance * distance));    
    //
    // /* remove attenuation from ambient, as otherwise at large distances the 
    //    light would be darker inside than outside the spotlight due the ambient 
    //    term in the else branch */
    // result += (diffuse + specular) * attenuation * intensity;
    //
    // frag_color = vec4(result, 1.0f);
    
}

// We assume that *normal* and *view_dir* is already normalized.
vec3 calc_dir_light(DirLight light, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(-light.direction);

    // ambient lighting
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));

    // diffuse lighting
    float diff = max(dot(light_dir, normal), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, tex_coords));

    // specular lighting
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, tex_coords));

    return (ambient + diffuse + specular);
}

// We assume that *normal* and *view_dir* is already normalized.
vec3 calc_point_light(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir)
{
    vec3 light_dir = normalize(light.position - frag_pos);

    // ambient lighting
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));

    // diffuse lighting
    float diff = max(dot(light_dir, normal), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, tex_coords));

    // specular lighting
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, tex_coords));

    // attenuation
    float distance    = length(light.position - frag_pos);
    float attenuation = 1.0 / 
        (light.constant +
        light.linear * distance +
        light.quadratic * (distance * distance));    

     return (ambient + diffuse + specular) * attenuation;
}

vec3 calc_spot_light(SpotLight light, vec3 normal, vec3 frag_pos, vec3 view_dir)
{
    vec3 light_dir = normalize(light.position - frag_pos);

    // ambient lighting
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));

    // diffuse lighting
    float diff = max(dot(light_dir, normal), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, tex_coords));

    // specular lighting
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, tex_coords));

    // attenuation
    float distance    = length(light.position - frag_pos);
    float attenuation = 1.0 / 
        (light.constant +
        light.linear * distance +
        light.quadratic * (distance * distance));    

    // spotlight intensity
    float theta     = dot(light_dir, normalize(-light.direction));
    float epsilon   = light.cutoff - light.outer_cutoff;
    float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0f, 1.0f);

    return (ambient + diffuse + specular) * attenuation * intensity;
}
