#version 330

layout(location=0) in vec4 vertex;

uniform mat4 mvp;

out vec3 position;

void main(void)
{
    position = vertex.xyz;
    gl_Position = mvp * vertex;
}
