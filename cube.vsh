#version 330

layout(location=0) in vec4 vertex;
layout(location=1) in vec3 normal;

uniform mat4 mvp;
uniform mat4 nm;

out vec3 position;

void main(void)
{
    position = vertex.xyz;
    gl_Position = mvp * vertex;
}
