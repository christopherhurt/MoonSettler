#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoordsIn;
layout (location = 2) in vec3 normal; // TODO: calculations with this

out vec2 texCoords;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main() {
	texCoords = texCoordsIn;
	gl_Position = projection * view * transform * vec4(pos, 1.0);
}