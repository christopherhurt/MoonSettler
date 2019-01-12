#version 330 core

out vec4 outColor;

uniform vec3 amount;

void main() {
	outColor = vec4(sin(amount.x), sin(amount.y), sin(amount.z), 1.0);
}