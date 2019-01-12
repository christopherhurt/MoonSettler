#version 330 core

in vec2 texCoords;

out vec4 outColor;

uniform vec3 amount;
uniform sampler2D tex;

void main() {
	vec4 controlledColor = vec4(sin(amount.x), sin(amount.y), sin(amount.z), 1.0);
	vec4 texColor = texture(tex, texCoords);
	outColor = mix(controlledColor, texColor, 0.5);
}