#include <fstream>
#include <iostream>
#include <vector>
#include <RawEngine/ShaderLoader.hpp>

#define glCheckStatus(TYPE, PNAME, OBJECT) do { GLint status; glGet##TYPE##iv(OBJECT, GL_##PNAME##_STATUS, &status); if (status != GL_TRUE) { GLchar message[1024]; glGet##TYPE##InfoLog(OBJECT, 1024, nullptr, message); std::cerr << message << std::endl; } } while(false)

std::vector<char> read_file(const std::filesystem::path& filename)
{
    std::ifstream stream(filename, std::ios::in | std::ios::ate);

    const int64_t size = stream.tellg();
    stream.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    stream.read(buffer.data(), size);

    stream.close();

    return buffer;
}

void add_shader(const GLuint program, const GLenum type, const std::filesystem::path& filename)
{
    const auto source = read_file(filename);
    const char* pSource = source.data();

    const auto shader = glCreateShader(type);
    glShaderSource(shader, 1, &pSource, nullptr);
    glCompileShader(shader);
    glCheckStatus(Shader, COMPILE, shader);
    glAttachShader(program, shader);
    glDeleteShader(shader);
}

RawEngine::ShaderLoader::~ShaderLoader()
{
    if (Program)
        glDeleteProgram(Program);
}

void RawEngine::ShaderLoader::Load(const std::filesystem::path& vertex_filename, const std::filesystem::path& fragment_filename)
{
    if (Program)
        glDeleteProgram(Program);
    Program = glCreateProgram();

    add_shader(Program, GL_VERTEX_SHADER, vertex_filename);
    add_shader(Program, GL_FRAGMENT_SHADER, fragment_filename);
    glLinkProgram(Program);
    glCheckStatus(Program, LINK, Program);
    glValidateProgram(Program);
    glCheckStatus(Program, VALIDATE, Program);
}
