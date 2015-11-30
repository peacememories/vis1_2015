#version 330

uniform sampler3D voxels;
uniform sampler2D backfaces;
uniform mat4 mm;
uniform vec2 windowSize;

in vec3 position;

out vec4 color;

void main(void)
{
    vec3 coords = position+vec3(0.5);
    vec4 lastPass = texture(backfaces, gl_FragCoord.xy/2+vec2(0.5));
    vec3 backface_pos = lastPass.rgb;
    //float brightness = length(backface_pos - coords);
    //color = vec4(vec3(brightness), 1.0);
    color = vec4(gl_FragCoord.xy, 0, 1.0);
}
