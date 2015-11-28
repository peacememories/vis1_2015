#version 330

uniform sampler3D voxels;

in vec3 position;

out vec4 color;

void main(void)
{
    float brightness = texture(voxels, (vec3(1,1,1)+position)/2).r;
    color = vec4(brightness, brightness, brightness, 1);//vec4(1,0,1,1);
}
