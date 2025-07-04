#include "Types.hpp"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Util.hpp"

Shader::Shader (std::string_view vert_shader_path, std::string_view frag_shader_path)
{
    uint vert_shader, frag_shader;
    std::string vert_source, frag_source;

    vert_source = read_file_contents(vert_shader_path); 
    vert_shader = Shader::generate_shader(GL_VERTEX_SHADER, vert_source.c_str());
    
    frag_source = read_file_contents(frag_shader_path); 
    frag_shader = Shader::generate_shader(GL_FRAGMENT_SHADER, frag_source.c_str());
    
    id = glCreateProgram();
    glAttachShader(id, vert_shader);
    glAttachShader(id, frag_shader);
    glLinkProgram(id);

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    Shader::check_shaderprg_link(id);
}

void Shader::use() const
{ glUseProgram(id); }

uint Shader::generate_shader(uint type, const char* shader_source)
{
    uint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
    Shader::check_shader_compile(shader);
    return shader;
}

void Shader::check_shader_compile(uint shader)
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


void Shader::check_shaderprg_link(uint program)
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
{ glUniform1i(glGetUniformLocation(id, name.data()), (int)value); }

void Shader::set(std::string_view name, int value) const
{ glUniform1i(glGetUniformLocation(id, name.data()), value); }

void Shader::set(std::string_view name, float value) const
{ glUniform1f(glGetUniformLocation(id, name.data()), value); }

void Shader::set(std::string_view name, const glm::mat2& mat) const
{ glUniformMatrix4fv(glGetUniformLocation(id, name.data()), 1, GL_FALSE, glm::value_ptr(mat)); }

void Shader::set(std::string_view name, const glm::mat3& mat) const
{ glUniformMatrix4fv(glGetUniformLocation(id, name.data()), 1, GL_FALSE, glm::value_ptr(mat)); }

void Shader::set(std::string_view name, const glm::mat4& mat) const
{ glUniformMatrix4fv(glGetUniformLocation(id, name.data()), 1, GL_FALSE, glm::value_ptr(mat)); }

void Shader::set(std::string_view name, const glm::vec3& vec) const
{ glUniform3fv(glGetUniformLocation(id, name.data()), 1, &vec[0]); }

void Shader::set(std::string_view name, float x, float y, float z) const
{ glUniform3f(glGetUniformLocation(id, name.data()), x, y, z); }

void Shader::set(std::string_view name, float x, float y, float z, float w) const
{ glUniform4f(glGetUniformLocation(id, name.data()), x, y, z, w); }

void Shader::set(std::string_view name, const glm::vec4& vec) const
{ glUniform4fv(glGetUniformLocation(id, name.data()), 1, &vec[0]); }
