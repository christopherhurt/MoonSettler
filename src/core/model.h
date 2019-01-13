#pragma once

#include "mesh.h"
#include "texture.h"

class Model {
public:
	inline Model(Mesh * meshIn, Texture * textureIn) : mesh(meshIn), texture(textureIn) {}
	void bind();
	~Model();
private:
	Mesh * mesh;
	Texture * texture;
};