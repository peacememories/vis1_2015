#version 330

uniform sampler2D backfaces;
uniform sampler3D voxels;
uniform mat4 mm;
uniform vec2 windowSize;
uniform vec3 myColor1;
uniform vec3 myColor2;
uniform vec3 myColor3;

in vec3 position;

out vec4 color;

float combineDensity(float front, float back) {
    return max(front, back);
}

float getDensity(vec3 frontFace, vec3 backFace, float distance) {
    vec3 position = (backFace-frontFace)*distance + frontFace;
    return texture(voxels, position).r;
}

vec4 getColor(vec3 colorA, float alphaA, vec3 colorB, float alphaB) {
    vec3 colorC = vec3(0.0, 0.0, 0.0);
    float alphaC = alphaA + (1-alphaA) * alphaB;
    colorC = 1/alphaC* (alphaA * colorA + (1-alphaA) * alphaB * colorB);
    return vec4(vec3(colorC), alphaC);
}

void main(void)
{
    vec2 pixelPos = gl_FragCoord.xy/windowSize;
    vec3 frontFace = position+vec3(0.5);
    vec3 backFace = texture(backfaces, pixelPos).xyz;

    vec4 colorC = vec4(0.0, 0.0, 0.0, 0.0);
     vec3 lastColor = vec3(0.0, 0.0, 0.0);
    float density = 0.0;
    float lastAlpha = 0.0;
    for(float x = 0; x < 1; x+=0.05) {
        density = combineDensity(density, getDensity(frontFace, backFace, x));
        if (density < 0.1) {
          colorC = vec4(lastColor, 1);
        } else if (density < 0.45 ) {
            colorC = vec4(getColor(myColor1, density, lastColor, lastAlpha));
        } else if (density < 0.5) {
             colorC = vec4(getColor(myColor2, density, lastColor, lastAlpha));
        } else {
            colorC = vec4(getColor(myColor3, density, lastColor, lastAlpha));
        }
        lastAlpha = colorC.a;
        lastColor = colorC.rgb;
    }
    color = colorC;
}
