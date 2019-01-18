#pragma once

#include "mesh.h"
#include "material.h"
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
						Mesh * meshIn, Material * materialIn, Shader * shaderIn) :
						x(xIn), y(yIn), z(zIn), rX(rXIn), rY(rYIn), rZ(rZIn), sX(sXIn), sY(sYIn), sZ(sZIn),
						mesh(meshIn), material(materialIn), shader(shaderIn) {}
	void render();
private:
	Mesh * mesh;
	Material * material;
	Shader * shader;
};