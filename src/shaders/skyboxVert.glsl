#version 330 core

layout (location = 0) in vec3 pos;

out vec3 texCoords;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main() {
	texCoords = pos;
	mat4 viewRot = mat4(mat3(view));
	gl_Position = (projection * viewRot * transform * vec4(pos, 1.0)).xyww;
}