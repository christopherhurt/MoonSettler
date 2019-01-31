#pragma once

#include <list>
#include <math.h>
#include "controls/camera.h"
#include "chunk.h"
#include "utils/unbind.h"
#include "rendering/material.h"
#include "terrainFactors.h"

class Terrain {
public:
	Terrain(Shader * shaderIn, Camera * camIn, Material * materialIn, unsigned long seedIn);
	void updateAndRender();
	float getPlayerHeightAt(float x, float z);
	~Terrain();
private:
	Shader * shader;
	Camera * cam;
	Material * material;
	unsigned long seed;
	list<Chunk *> * chunks;
};