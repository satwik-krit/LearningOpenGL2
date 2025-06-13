#include <fstream>
#include <string_view>
#include <iostream>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Types.h"
#include "Shader.h"
#include "Util.h"

Shader::Shader (std::string_view vert_shader_path, std::string_view frag_shader_path)
{
    uint vert_shader, frag_shader;
    std::string vert_source, frag_source;

    vert_source = read_file_contents(vert_shader_path); 
    vert_shader = Shader::_generate_shader(GL_VERTEX_SHADER, vert_source.c_str());
    
    frag_source = read_file_contents(frag_shader_path); 
    frag_shader = Shader::_generate_shader(GL_FRAGMENT_SHADER, frag_source.c_str());
    
    this->id = glCreateProgram();
    const uint& id = this->id;
    glAttachShader(id, vert_shader);
    glAttachShader(id, frag_shader);
    glLinkProgram(id);

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    Shader::_check_shaderprg_link(id);
}

void Shader::use() const
{ glUseProgram(this->id); }

uint Shader::_generate_shader(uint type, const char* shader_source)
{
    uint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
    Shader::_check_shader_compile(shader);
    return shader;
}

void Shader::_check_shader_compile(uint shader)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        int infoLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
        char* info = new char[infoLength];
        glGetShaderInfoLog(shader, infoLength, NULL, info);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION\n" << info << '\n';
        delete[] info;
    }
}


void Shader::_check_shaderprg_link(uint program)
{
    int success;
    glGetProgramiv(program, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        int infoLength;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &infoLength);
        char* info = new char[infoLength];
        glGetShaderInfoLog(program, infoLength, NULL, info);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING\n" << info << '\n';
        delete[] info;
    }
}

void Shader::set(std::string_view name, bool value) const
{ glUniform1i(glGetUniformLocation(this->id, name.data()), (int)value); }

void Shader::set(std::string_view name, int value) const
{ glUniform1i(glGetUniformLocation(this->id, name.data()), value); }

void Shader::set(std::string_view name, float value) const
{ glUniform1f(glGetUniformLocation(this->id, name.data()), value); }

void Shader::set(std::string_view name, const glm::mat2& mat) const
{ glUniformMatrix4fv(glGetUniformLocation(this->id, name.data()), 1, GL_FALSE, glm::value_ptr(mat)); }

void Shader::set(std::string_view name, const glm::mat3& mat) const
{ glUniformMatrix4fv(glGetUniformLocation(this->id, name.data()), 1, GL_FALSE, glm::value_ptr(mat)); }

void Shader::set(std::string_view name, const glm::mat4& mat) const
{ glUniformMatrix4fv(glGetUniformLocation(this->id, name.data()), 1, GL_FALSE, glm::value_ptr(mat)); }

