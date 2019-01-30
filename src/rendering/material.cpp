#include "material.h"

Material::Material(Vec3 * colorIn, float ambientIn, float diffuseIn, float specularIn, int shininessIn) : color(colorIn), ambient(ambientIn), diffuse(diffuseIn), specular(specularIn), shininess(shininessIn) {
	diffuseMap = nullptr;
}

void Material::loadAndBind(Shader &shader) {
	if (diffuseMap != nullptr) {
		diffuseMap->bindToUnit(0);
	}
	
	shader.setVec3("material.color", *color);
	shader.setBool("material.useDiffuseMap", diffuseMap != nullptr);
	shader.setFloat("material.ambient", ambient);
	shader.setFloat("material.diffuse", diffuse);
	shader.setFloat("material.specular", specular);
	shader.setInt("material.shininess", shininess);
}

Material::~Material() {
	delete color;

	if (diffuseMap != nullptr) {
		delete diffuseMap;
	}
}