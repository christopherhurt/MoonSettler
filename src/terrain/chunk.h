#pragma once

#include "rendering/mesh.h"
#include "rendering/texture.h"
#include "terrainGen.h"
#include "math/mat4.h"
#include "utils/matGen.h"
#include "rendering/shader.h"

class Chunk {
public:
	Chunk(int xIn, int zIn, float scale, float amplitude, unsigned long seed);
	void render(Shader * shader);
	inline int getX() { return x; }
	inline int getZ() { return z; }
	~Chunk();
private:
	int x;
	int z;
	Mesh * mesh;
	Mat4 * transform;
};