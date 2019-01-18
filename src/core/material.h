#pragma once

#include "texture.h"

class Material {
public:
	Material(Texture * textureIn, float ambientIn, float diffuseIn, float specularIn, int shininessIn);
	void loadAndBind();
	inline void bindNormalMap(Texture * normalMapIn) { normalMap = normalMapIn; }
	inline ~Material() { delete texture; }
private:
	Texture * texture;
	Texture * normalMap;
	float ambient;
	float diffuse;
	float specular;
	int shininess;
};