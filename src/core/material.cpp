#include "material.h"

void Material::loadAndBind(Shader &shader) {
	diffuseMap->bindToUnit(0);
	
	shader.setFloat("material.ambient", ambient);
	shader.setFloat("material.diffuse", diffuse);
	shader.setFloat("material.specular", specular);
	shader.setInt("material.shininess", shininess);
}