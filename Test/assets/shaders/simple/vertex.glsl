#version 460 core

layout (location = 0) in vec4 POSITION;
layout (location = 1) in vec3 NORMAL;
layout (location = 2) in vec2 TEXCOORDS;

uniform mat4 MODEL = mat4(1.0);
uniform mat4 VIEW = mat4(1.0);
uniform mat4 PROJ = mat4(1.0);

out vec4 position;
out vec3 normal;
out vec2 texcoords;

void main()
{
    position = PROJ * VIEW * MODEL * POSITION;
    normal = NORMAL;
    texcoords = TEXCOORDS;
}
