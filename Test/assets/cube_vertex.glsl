#version 450 core

in vec4 IN_POSITION;
in vec3 IN_NORMAL;
in vec2 IN_UV;

uniform mat4 IN_MODEL;
uniform mat4 IN_VIEW;
uniform mat4 IN_PROJ;

out vec4 position;
out vec3 normal;
out vec2 uv;

void main()
{
    position = IN_PROJ * IN_VIEW * IN_MODEL * IN_POSITION;
    normal = IN_NORMAL;
    uv = IN_UV;
}
