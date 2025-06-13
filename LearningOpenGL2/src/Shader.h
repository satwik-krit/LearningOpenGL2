#pragma once

#include <string>
#include <string_view>

#include "Types.h"

class Shader
{
public:
    uint id;
    
    Shader (std::string_view vert_shader_path, std::string_view frag_shader_path);
    
    void use() const;
    void set(std::string_view name, bool value) const;
    void set(std::string_view name, int value) const;
    void set(std::string_view name, float value) const;

    static uint _generate_shader(uint type, const char* shader_source);
    static void _check_shader_compile(uint shader);
    static void _check_shaderprg_link(uint program);
};
