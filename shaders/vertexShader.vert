#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 Color;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
    Color = color;
    gl_Position = model * vec4(position, 1.0);
}