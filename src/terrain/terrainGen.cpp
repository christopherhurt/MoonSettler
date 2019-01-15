#include "terrainGen.h"

static float * genSimpleGrid(int chunkX, int chunkZ, unsigned long seed);

Mesh * genTerrainChunk(int chunkX, int chunkZ, unsigned long seed) {
	float * simpleGrid = genSimpleGrid(chunkX, chunkZ, seed);

	// TODO: generate smooth noise by averaging simple grid

	delete simpleGrid;
}

static float * genSimpleGrid(int chunkX, int chunkZ, unsigned long seed) {
	int numVertices = POINTS_PER_CHUNK * POINTS_PER_CHUNK;
	int verticesSize = numVertices * 3;
	float * vertices = new float[verticesSize];
	float baseX = chunkX - 0.5f;
	float baseZ = chunkZ - 0.5f;
	float inc = 1.0f / (POINTS_PER_CHUNK - 1);

	for (int i = 0; i < numVertices; i++) {
		float x = baseX + (i % POINTS_PER_CHUNK) * inc;
		float z = baseZ + (i / POINTS_PER_CHUNK) * inc;

		unsigned int pseudoSeed = (unsigned int)(x * 8934769492) + (unsigned int)(z * 6294609218) + seed;
		srand(pseudoSeed);
		float y = (float)rand() / RAND_MAX - 0.5f;

		int xOff = i * 3;
		int yOff = i * 3 + 1;
		int zOff = i * 3 + 2;

		*(vertices + xOff) = x;
		*(vertices + yOff) = y;
		*(vertices + zOff) = z;
	}

	return vertices;
}