#version 460 core
in vec2 UV;
smooth in vec3 smoothColour;
flat in vec3 flatColour;

out vec4 colour;

uniform sampler2D givenTexture;
uniform bool flatMode;
uniform float colourSpeed;
uniform bool colourMode;
uniform bool greyscaleMode;

vec3 rgb2hsv(vec3 c) {
    vec4 K = vec4(0.f, -1.f / 3.f, 2.f / 3.f, -1.f);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;

    return vec3(abs(q.z + (q.w - q.y) / (6.f * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.f, 2.f / 3.f, 1.f / 3.f, 3.f);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.f - K.www);

    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.f, 1.f), c.y);
}

void main() {
    vec3 hsv;
    float grey;

    if (flatMode) {
        hsv = rgb2hsv(flatColour.rgb);
        grey = (0.2125 * flatColour.x +
                0.2125 * flatColour.y +
                0.2125 * flatColour.z);
    } else {
        hsv = rgb2hsv(smoothColour.rgb);
        grey = (0.2125 * smoothColour.x +
                0.2125 * smoothColour.y +
                0.2125 * smoothColour.z);
    }

    hsv.x += colourSpeed;

    if (colourMode)
        colour = vec4(hsv2rgb(hsv), 1.f);
    else if (greyscaleMode)
        colour = vec4(grey, grey, grey, 1.f);
    else
        colour = vec4(texture(givenTexture, UV).rgb, 1.f);
}