#pragma once

#include <list>
#include <math.h>
#include "controls/camera.h"
#include "chunk.h"
#include "utils/unbind.h"
#include "rendering/material.h"
#include "terrainGen.h"

constexpr float TERRAIN_SCALE = 10;
constexpr float TERRAIN_AMPLITUDE = 40;

constexpr int CHUNK_WIDTH = CHUNK_SIZE - 1;
constexpr int VIEW_DISTANCE = 2;
constexpr int MAX_CHUNKS_LOADED = 1000;

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