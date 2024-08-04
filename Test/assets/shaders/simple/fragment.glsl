#version 460 core

layout (location = 0) out vec4 OUT_COLOR;

uniform vec3 COLOR = vec3(0.99);

in vec4 position;
in vec3 normal;
in vec2 texcoords;

const vec3 SUN_DIRECTION = normalize(vec3(0.1, 1.0, -0.6));

void main()
{
    OUT_COLOR = vec4(COLOR * max(0.05, dot(normal, SUN_DIRECTION)), 1.0);
}
