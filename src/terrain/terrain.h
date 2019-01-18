#pragma once

#include <list>
#include <math.h>
#include "core/camera.h"
#include "chunk.h"
#include "utils/unbind.h"

constexpr int CHUNK_WIDTH = CHUNK_SIZE - 1;
constexpr int VIEW_DISTANCE = 3;
constexpr int MAX_CHUNKS_LOADED = 1000;

class Terrain {
public:
	Terrain(float scaleIn, float amplitudeIn, Shader * shaderIn, Camera * camIn, Texture * textureIn, unsigned long seedIn);
	void updateAndRender();
	~Terrain();
private:
	float scale;
	float amplitude;
	Shader * shader;
	Camera * cam;
	Texture * texture;
	unsigned long seed;
	list<Chunk *> * chunks;
};