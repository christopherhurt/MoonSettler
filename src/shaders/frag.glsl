#version 330 core

in vec2 texCoords;
in vec3 normal;
in vec3 toCam;

out vec4 outColor;

struct Material {
	sampler2D diffuseMap;
	float ambient;
	float diffuse;
	float specular;
	int shininess;
};

struct Light {
	vec3 color;
	float intensity;
};

struct DirectionalLight {
	Light basic;
	vec3 direction;
};

const int LIGHT_LEVELS = 4;

uniform Material material;
uniform DirectionalLight directionalLight;

void main() {
	vec3 diffuseMapColor = texture(material.diffuseMap, texCoords).xyz;
	vec3 lightColor = directionalLight.basic.color;

	float ambientFactor = material.ambient;

	float diffuseAmt = max(dot(normal, -directionalLight.direction), 0.0);
	float diffuseFactor = material.diffuse * diffuseAmt;

	vec3 reflection = reflect(directionalLight.direction, normal);
	float specularAmt = pow(max(dot(toCam, reflection), 0.0), material.shininess);
	vec3 specular = material.specular * specularAmt * lightColor;
	
	float ambientDiffuseFactor = ambientFactor + diffuseFactor;
	ambientDiffuseFactor = floor(ambientDiffuseFactor * LIGHT_LEVELS) / LIGHT_LEVELS;
	vec3 ambientDiffuse = ambientDiffuseFactor * lightColor;

	vec3 finalColor = diffuseMapColor * ambientDiffuse + specular;
	outColor = vec4(finalColor, 1.0);
}