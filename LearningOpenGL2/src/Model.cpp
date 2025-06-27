#include "Types.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include "Model.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Util.hpp"

Model::Model(std::string_view path)
{
    load_model(path);
}

void Model::draw(Shader& shader)
{
    for (uint i = 0; i < meshes.size(); i++)
        meshes[i].draw(shader);
}

void Model::load_model(std::string_view path)
{
    std::cout << "LOADING MODEL: " << path << std::endl;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(static_cast<std::string>(path), 
                                             aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    meshes.reserve(scene->mRootNode->mNumChildren);
    process_node(scene->mRootNode, scene);

    std::cout << "DONE\n";
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
    // process meshes of *node*
    for (uint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(mesh, scene));
    }

    // process meshes of the children
    for (uint i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], scene);
    }
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    std::vector<Texture> texture;
    Vertex vertex;
    aiVector3D ai_vector;
    glm::vec3 vector;
    glm::vec2 _vector;
    glm::vec2 default_tex_coord = glm::vec2(0.0f, 0.0f);
    aiFace face;
    
    // check if the mesh contains texture coordinates.
    bool has_texture_coords = (mesh->mTextureCoords[0]) ? true : false;
    bool has_normals = (mesh->HasNormals()) ? true : false;

    // Reserve space to avoid unnecessary resizing.
    vertices.reserve(mesh->mNumVertices);

    for (uint i = 0; i < mesh->mNumVertices; i++)
    {
        ai_vector = mesh->mVertices[i];
        vector.x = ai_vector.x;
        vector.y = ai_vector.y;
        vector.z = ai_vector.z;
        vertex.position = vector;

        if (has_normals) {
            ai_vector = mesh->mNormals[i];
            vector.x = ai_vector.x;
            vector.y = ai_vector.y;
            vector.z = ai_vector.z;
            vertex.normal = vector;
        }

        if (has_texture_coords) {
            // A vertex can contain up to 8 different texture coordinates.
            // We thus make the assumption that we won't use models where a 
            // vertex can have multiple texture coordinates so we always take 
            // the first set (0).
            ai_vector = mesh->mTextureCoords[0][i];
            _vector.x = ai_vector.x;
            _vector.y = ai_vector.y;
            vertex.tex_coords = _vector;
        } else { vertex.tex_coords = default_tex_coord; }
        vertices.push_back(vertex);
    }
    
    for (uint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (uint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuse_maps =
            load_material_textures(material, aiTextureType_DIFFUSE, TEXTURE_DIFFUSE);
        texture.insert(texture.end(), diffuse_maps.begin(), diffuse_maps.end());

        std::vector<Texture> specular_maps = 
            load_material_textures(material, aiTextureType_SPECULAR, TEXTURE_SPECULAR);
        texture.insert(texture.end(), specular_maps.begin(), specular_maps.end());
    }

    return Mesh(vertices, indices, texture);
}

std::vector<Texture>  
Model::load_material_textures(aiMaterial* mat, aiTextureType ai_type, TextureType type)
{
    bool already_loaded = false;
    aiString str;
    Texture texture;
    std::vector<Texture> textures;
    textures.reserve(mat->GetTextureCount(ai_type));

    for (uint i = 0; i < mat->GetTextureCount(ai_type); i++) {
        already_loaded = false;
        for (uint j = 0; j < textures_loaded.size(); j++) {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
                // If the paths are same, we have already loaded that texture.
                // Simply add it to *textures* without re-reading it.
                textures.push_back(textures_loaded[j]);
                already_loaded = true;
                break;
            }
        }

        if (!already_loaded) {
            mat->GetTexture(ai_type, i, &str);
            texture.id = texture_from_file(str.C_Str(), directory);
            texture.type = type;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;
}
