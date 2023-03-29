#version 460 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 vertexUV;
layout (location = 2) in vec3 vertexColour;

out vec2 UV;
smooth out vec3 smoothColour;
flat out vec3 flatColour;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(vertexPos, 1.f);
    UV = vertexUV;
    smoothColour = vertexColour;
    flatColour = vertexColour;
}