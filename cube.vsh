#version 330

layout(location=0) in vec4 vertex;
layout(location=1) in vec3 normal;
void main(void)
{
    gl_Position = vertex;
}
