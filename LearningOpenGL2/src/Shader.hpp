#pragma once

#include <string>
#include <string_view>

#include "glm/glm.hpp"

#include "Types.hpp"

class Shader
{
public:
    uint id;
    
    Shader (std::string_view vert_shader_path, std::string_view frag_shader_path);
    
    void use() const;
    void set(std::string_view name, bool value) const;
    void set(std::string_view name, int value) const;
    void set(std::string_view name, float value) const;
    void set(std::string_view name, const glm::mat2& mat) const;
    void set(std::string_view name, const glm::mat3& mat) const;
    void set(std::string_view name, const glm::mat4& mat) const;
    void set(std::string_view name, const glm::vec3& vec) const;
    void set(std::string_view name, float x, float y, float z) const;
    void set(std::string_view name, float x, float y, float z, float w) const;
    void set(std::string_view name, const glm::vec4& vec) const;

    static uint generate_shader(uint type, const char* shader_source);
    static void check_shader_compile(uint shader);
    static void check_shaderprg_link(uint program);
};
