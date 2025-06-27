#pragma once

#include "Types.hpp"

#include <glm/glm.hpp>

#include "Shader.hpp"


struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
};

enum TextureType
{
    TEXTURE_DIFFUSE = 1,
    TEXTURE_SPECULAR
};

struct Texture
{
    uint id;
    TextureType type;
    std::string_view path;
};

class Mesh
{
public:
    std::vector<Vertex>  vertices;
    std::vector<uint>    indices;
    std::vector<Texture> textures;

private:
    uint VAO, VBO, EBO;

public:
    Mesh(std::vector<Vertex> vertices,
         std::vector<uint> indices, 
         std::vector<Texture> textures);
    void draw(Shader &shader);
    
private:
    void setup();
};
