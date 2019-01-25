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

uniform Material material;
uniform DirectionalLight directionalLight;

void main() {
	vec3 diffuseMapColor = texture(material.diffuseMap, texCoords).xyz;
	vec3 lightColor = directionalLight.basic.color;

	vec3 ambient = material.ambient * lightColor;

	float diffuseAmt = max(dot(normal, -directionalLight.direction), 0.0);
	vec3 diffuse = material.diffuse * diffuseAmt * lightColor;

	vec3 reflection = reflect(directionalLight.direction, normal);
	float specularAmt = pow(max(dot(toCam, reflection), 0.0), material.shininess);
	vec3 specular = material.specular * specularAmt * lightColor;
	
	vec3 finalColor = diffuseMapColor * (ambient + diffuse) + specular;
	outColor = vec4(finalColor, 1.0);
}