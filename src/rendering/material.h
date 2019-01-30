#pragma once

#include "texture.h"
#include "rendering/shader.h"

class Material {
public:
	Material(Vec3 * colorIn, float ambientIn, float diffuseIn, float specularIn, int shininessIn);
	void loadAndBind(Shader &shader);
	inline void attachDiffuseMap(Texture * diffuseMapIn) { diffuseMap = diffuseMapIn; }
	~Material();
private:
	Vec3 * color;
	Texture * diffuseMap;
	float ambient;
	float diffuse;
	float specular;
	int shininess;
};