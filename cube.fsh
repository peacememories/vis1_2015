#version 330

uniform sampler3D voxels;

in vec3 position;

out vec4 color;

void main(void)
{
    vec3 coords = position+vec3(0.5);
    //color = vec4(coords, texture(voxels, coords).r);
    color = vec4(1);
}
