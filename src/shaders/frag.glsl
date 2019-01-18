#version 330 core

in vec2 texCoords;

out vec4 outColor;

struct Material {
	sampler2D diffuseMap;
	sampler2D normalMap;
	float ambient;
	float diffuse;
	float specular;
	int shininess;
	int usingNormalMap;
};

struct Light {
	vec3 color;
	float intensity;
};

struct DirectionalLight {
	Light basic;
	vec3 direction;
};

uniform Material material;
uniform DirectionalLight directionalLight;

void main() {
	// TODO: apply directional light, do normals importing, check material texture bindings
	//outColor = texture(tex, texCoords);
	outColor = vec4(1.0, 0.0, 0.0, 1.0);
}