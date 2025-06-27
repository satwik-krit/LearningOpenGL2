#include "Types.hpp"

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "Mesh.hpp"
#include "Shader.hpp"


Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<uint> indices,
           std::vector<Texture> textures)
    : vertices(vertices), indices(indices), textures(textures)
{
    setup();
}

void Mesh::setup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), 
                 &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), 
                 &indices[0], GL_STATIC_DRAW);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                          (void*)offsetof(Vertex, normal));

    // texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                          (void*)offsetof(Vertex, tex_coords));

    // Unbind the VAO
    glBindVertexArray(0);
}

void Mesh::draw(Shader& shader)
{
    uint diffuse_index = 1, specular_index = 1;

    for (uint i= 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string name = "material.texture";

        switch(textures[i].type)
        {
            case TEXTURE_DIFFUSE: 
                name = "diffuse" + std::to_string(diffuse_index++);
                break;
            case TEXTURE_SPECULAR:
                name = "specular" + std::to_string(specular_index++);
                specular_index++;
                break;
        }
        shader.set(name, (int)textures[i].id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

}
