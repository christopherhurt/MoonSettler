#pragma once

#include "texture.h"
#include "core/shader.h"

class Material {
public:
	inline Material(Texture * diffuseMapIn, float ambientIn, float diffuseIn, float specularIn, int shininessIn) : diffuseMap(diffuseMapIn), ambient(ambientIn), diffuse(diffuseIn), specular(specularIn), shininess(shininessIn) {}
	void loadAndBind(Shader &shader);
	inline ~Material() { delete diffuseMap; }
private:
	Texture * diffuseMap;
	float ambient;
	float diffuse;
	float specular;
	int shininess;
};