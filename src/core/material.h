#pragma once

#include "texture.h"
#include "core/shader.h"

class Material {
public:
	Material(Texture * diffuseMapIn, float ambientIn, float diffuseIn, float specularIn, int shininessIn);
	void loadAndBind(Shader &shader);
	inline void attachNormalMap(Texture * normalMapIn) { normalMap = normalMapIn; }
	inline ~Material() { delete diffuseMap; delete normalMap; }
private:
	Texture * diffuseMap;
	Texture * normalMap;
	float ambient;
	float diffuse;
	float specular;
	int shininess;
};