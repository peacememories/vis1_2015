#version 330

uniform sampler2D backfaces;
uniform sampler3D voxels;
uniform mat4 mm;
uniform vec2 windowSize;
uniform vec3 myColor;

in vec3 position;

out vec4 color;

float combineDensity(float front, float back) {
    return max(front, back);
}

float getDensity(vec3 frontFace, vec3 backFace, float distance) {
    vec3 position = (backFace-frontFace)*distance + frontFace;
    return texture(voxels, position).r;
}

vec3 getColor(vec3 colorA, float alphaA, vec3 colorB, float alphaB) {
    vec3 colorC = vec3(0.0, 0.0, 0.0);
    float alphaC = alphaA + (1-alphaA) * alphaB;
    colorC = 1/alphaC * (alphaA * colorA + (1-alphaA) * alphaB * colorB);
    return vec3(colorC);
}

void main(void)
{
    vec2 pixelPos = gl_FragCoord.xy/windowSize;
    vec3 frontFace = position+vec3(0.5);
    vec3 backFace = texture(backfaces, pixelPos).xyz;

    vec3 colorC = vec3(0.0, 0.0, 0.0);
    float density = 0.0;
    float lastDensity = 0.0;
    for(float x = 0; x < 1; x+=0.001) {
        density = combineDensity(density, getDensity(frontFace, backFace, x));
        colorC = vec3(getColor(myColor, density, vec3(0.0, 0.0, 0.0), lastDensity));
        lastDensity = density;
    }
    color = vec4(vec3(colorC), 1);
}
