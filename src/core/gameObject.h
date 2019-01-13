#pragma once

#include "mesh.h"
#include "texture.h"
#include "utils/unbind.h"

class GameObject {
public:
	inline GameObject(Mesh * meshIn, Texture * textureIn) : mesh(meshIn), texture(textureIn) {}
	void render();
	~GameObject();
private:
	Mesh * mesh;
	Texture * texture;
};