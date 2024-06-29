#version 450 core

in vec4 position;
in vec3 normal;
in vec2 uv;

uniform vec3 COLOR = vec3(0.99);

out vec4 OUT_COLOR;

const vec3 SUN_DIRECTION = normalize(vec3(0.1, 1.0, -0.6));

void main()
{
    OUT_COLOR = vec4(COLOR * max(0.05, dot(normal, -SUN_DIRECTION)), 1.0);
}
