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
	Terrain(Shader * shaderIn, Camera * camIn, Material * materialIn, unsigned int seedIn);
	void updateAndRender();
	float getPlayerHeightAt(float x, float z);
	~Terrain();
private:
	Shader * shader;
	Camera * cam;
	Material * material;
	unsigned int seed;
	list<Chunk *> * chunks;
};