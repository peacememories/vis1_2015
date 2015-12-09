#version 330

uniform sampler2D backfaces;
uniform sampler3D voxels;
uniform mat4 mm;
uniform vec2 windowSize;
uniform vec3 myColor;

in vec3 position;

out vec4 color;

vec4 combineColor(vec4 front, vec4 back) {
    float alpha = front.a+(1-front.a)*back.a;
    vec3 color = front.rgb+back.rgb*(1-front.a);
    return vec4(color, alpha);
}

float getDensity(vec3 frontFace, vec3 backFace, float distance) {
    vec3 position = (backFace-frontFace)*distance + frontFace;
    return texture(voxels, position).r;
}

vec4 densityToColor(float density) {
    float alpha = density*0.01;
    vec3 color = vec3(0,0,1);
    if(density < 0.1) {
        alpha = 0;
    } else if(density < 0.3) {
        color = vec3(1,0,0);
    } else if(density < 0.6) {
        color = vec3(0,1,0);
    }
    return vec4(color*alpha, alpha);
}

void main(void)
{
    vec2 pixelPos = gl_FragCoord.xy/windowSize;
    vec3 frontFace = position+vec3(0.5);
    vec3 backFace = texture(backfaces, pixelPos).xyz;

    vec4 incColor = vec4(0);
    for(float x = 0; x < 1; x+=0.001) {
        vec4 newColor = densityToColor(getDensity(frontFace, backFace, x));
        incColor = combineColor(incColor, newColor);
    }
    color = vec4(incColor.rgb*incColor.a, incColor.a);
}
