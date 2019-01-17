#pragma once

#include "mesh.h"
#include "texture.h"
#include "utils/unbind.h"
#include "shader.h"
#include "utils/matGen.h"

using namespace std;

class GameObject {
public:
	float x;
	float y;
	float z;
	float rX;
	float rY;
	float rZ;
	float sX;
	float sY;
	float sZ;

	inline GameObject(	float xIn, float yIn, float zIn,
						float rXIn, float rYIn, float rZIn,
						float sXIn, float sYIn, float sZIn,
						Mesh * meshIn, Texture * textureIn, Shader * shaderIn) :
						x(xIn), y(yIn), z(zIn), rX(rXIn), rY(rYIn), rZ(rZIn), sX(sXIn), sY(sYIn), sZ(sZIn),
						mesh(meshIn), texture(textureIn), shader(shaderIn) {}
	void render();
private:
	Mesh * mesh;
	Texture * texture;
	Shader * shader;
};