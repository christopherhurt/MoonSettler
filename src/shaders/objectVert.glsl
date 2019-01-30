#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoordsIn;
layout (location = 2) in vec3 normalIn;

out vec2 texCoords;
out vec3 normal;
out vec3 toCam;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 camLoc;

void main() {
	texCoords = texCoordsIn;
	normal = normalize(mat3(transpose(inverse(transform))) * normalIn);

	vec4 worldPos = transform * vec4(pos, 1.0);
	toCam = camLoc - worldPos.xyz;
	gl_Position = projection * view * worldPos;
}