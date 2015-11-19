#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv_coord;
uniform mat4 mvp;
out vec2 uv;

void main(void)
{
    gl_Position = mvp * vec4(position, 1);
    uv = uv_coord;
}

