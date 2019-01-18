#include "material.h"

Material::Material(Texture * textureIn, float ambientIn, float diffuseIn, float specularIn, int shininessIn) : texture(textureIn), ambient(ambientIn), diffuse(diffuseIn), specular(specularIn), shininess(shininessIn) {
	normalMap = nullptr;
}

void Material::loadAndBind() {
	// TODO: bind texture, normal map (if not null), load uniform on whether normal map is bound (null or not), and load uniforms
}