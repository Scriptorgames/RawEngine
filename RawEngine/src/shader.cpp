#include <fstream>
#include <iostream>
#include <RawEngine/Shader.hpp>

#define CHECK(ERR, SRC, TYPE, OBJECT, PARAM) {\
        GLint status;\
        glGet##TYPE##iv(OBJECT, PARAM, &status);\
        if (status != GL_TRUE) {\
            GLsizei length = 0;\
            GLchar message[1024];\
            glGet##TYPE##InfoLog(OBJECT, 1024, &length, message);\
            ERR << "In " << SRC << ":" << std::endl << message;\
        }\
    }

RawEngine::Shader::Shader(const std::string& id,
                          const std::map<ShaderStage, std::vector<std::filesystem::path>>& sources)
    : m_Id(id), m_Sources(sources)
{
}

static std::string read_string(const std::filesystem::path& path)
{
    std::ifstream stream(path, std::ios::in | std::ios::ate);
    if (!stream)
        throw std::runtime_error("read_string");

    const auto size = stream.tellg();
    stream.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    stream.read(buffer.data(), size);

    return buffer.data();
}

void RawEngine::Shader::Load()
{
    auto program = glCreateProgram();

    for (const auto& [stage, sources] : m_Sources)
    {
        GLenum type;
        switch (stage)
        {
        case ShaderStage_Vertex:
            type = GL_VERTEX_SHADER;
            break;
        case ShaderStage_Fragment:
            type = GL_FRAGMENT_SHADER;
            break;
        default:
            type = 0;
            break;
        }

        for (const auto& source : sources)
        {
            auto source_string = read_string(source);
            auto char_source = source_string.c_str();

            const auto shader = glCreateShader(type);
            glShaderSource(shader, 1, &char_source, nullptr);
            glCompileShader(shader);
            CHECK(std::cerr, source, Shader, shader, GL_COMPILE_STATUS)

            glAttachShader(program, shader);
            glDeleteShader(shader);
        }
    }

    glLinkProgram(program);
    CHECK(std::cerr, m_Id, Program, program, GL_LINK_STATUS)

    glValidateProgram(program);
    CHECK(std::cerr, m_Id, Program, program, GL_VALIDATE_STATUS)

    std::swap(m_Program, program);
    glDeleteProgram(program);
}
