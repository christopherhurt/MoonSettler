#include "material.h"

Material::Material(Texture * diffuseMapIn, float ambientIn, float diffuseIn, float specularIn, int shininessIn) : diffuseMap(diffuseMapIn), ambient(ambientIn), diffuse(diffuseIn), specular(specularIn), shininess(shininessIn) {
	normalMap = nullptr;
}

void Material::loadAndBind(Shader &shader) {
	diffuseMap->bindToUnit(0);

	bool usingNormalMap = normalMap != nullptr;
	if (usingNormalMap) {
		normalMap->bindToUnit(1);
	}
	
	shader.setFloat("material.ambient", ambient);
	shader.setFloat("material.diffuse", diffuse);
	shader.setFloat("material.specular", specular);
	shader.setInt("material.shininess", shininess);

	shader.setBool("material.usingNormalMap", usingNormalMap);
}