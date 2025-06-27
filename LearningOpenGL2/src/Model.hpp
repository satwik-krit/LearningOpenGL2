#pragma once

#include "Types.hpp"

#include <assimp/scene.h>

#include "Shader.hpp"
#include "Mesh.hpp"

class Model
{
private:
    std::vector<Mesh> meshes;
    std::string_view directory;
    std::vector<Texture> textures_loaded;
public:
    Model(std::string_view path);
    void draw(Shader& shader);
private:
    void load_model(std::string_view path);
    void process_node(aiNode* node, const aiScene* scene);
    Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture>  load_material_textures(aiMaterial* mat,
                                                 aiTextureType ai_type,
                                                 TextureType type);
};
