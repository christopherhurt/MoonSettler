#include "terrainGen.h"

static constexpr unsigned int POINTS_PER_SIDE = 4;
static constexpr unsigned int SAMPLES_PER_UNIT = 16;
static constexpr unsigned int VERTICES_PER_SIDE = POINTS_PER_SIDE + (SAMPLES_PER_UNIT - 1) * (POINTS_PER_SIDE - 1);
static constexpr float SMALL_INC = 1 / (VERTICES_PER_SIDE - 1.0f);
static constexpr float LARGE_INC = 1 / (POINTS_PER_SIDE - 1.0f);

static float getInterpolatedHeightAt(float x, float z, int offXDeg, int offZDeg, float smallInc, float largeInc, unsigned long seed);
static float getAverageHeightAt(float x, float z, float inc, unsigned long seed);
static float getHeightAt(float x, float z, unsigned long seed);

// TODO: fix
Mesh * genTerrainChunk(int chunkX, int chunkZ, unsigned long seed) {
	unsigned int verticesLength = VERTICES_PER_SIDE * VERTICES_PER_SIDE * 3;
	unsigned int texCoordsLength = VERTICES_PER_SIDE * VERTICES_PER_SIDE * 2;
	unsigned int indicesLength = (VERTICES_PER_SIDE - 1) * (VERTICES_PER_SIDE - 1) * 6;

	float * vertices = new float[verticesLength];
	float * texCoords = new float[texCoordsLength];
	unsigned int * indices = new unsigned int[indicesLength];

	int index = 0;
	for (int currZ = 0; currZ < VERTICES_PER_SIDE; currZ++) {
		for(int currX = 0; currX < VERTICES_PER_SIDE; currX++) {
			float texU = currX * SMALL_INC;
			float texV = currZ * SMALL_INC;

			float vertX = 1 - texU + chunkX - 0.5f;
			float vertZ = texV + chunkZ - 0.5f;
			
			float vertY;
			int offXDeg = currX % SAMPLES_PER_UNIT;
			int offZDeg = currZ % SAMPLES_PER_UNIT;
			if (offXDeg == 0 && offZDeg == 0) {
				vertY = getAverageHeightAt(vertX, vertZ, LARGE_INC, seed);
			}
			else {
				vertY = getInterpolatedHeightAt(vertX, vertZ, offXDeg, offZDeg, SMALL_INC, LARGE_INC, seed);
			}
			
			vertices[index * 3] = vertX;
			vertices[index * 3 + 1] = vertY;
			vertices[index * 3 + 2] = vertZ;

			texCoords[index * 2] = texU;
			texCoords[index * 2 + 1] = texV;

			index++;
		}
	}

	index = 0;
	for (int blockZ = 0; blockZ < VERTICES_PER_SIDE - 1; blockZ++) {
		for (int blockX = 0; blockX < VERTICES_PER_SIDE - 1; blockX++) {
			int bottomLeft = blockZ * VERTICES_PER_SIDE + blockX;
			int topLeft = (blockZ + 1) * VERTICES_PER_SIDE + blockX;
			int topRight = topLeft + 1;
			int bottomRight = bottomLeft + 1;

			indices[index++] = bottomLeft;
			indices[index++] = topLeft;
			indices[index++] = topRight;
			indices[index++] = topRight;
			indices[index++] = bottomRight;
			indices[index++] = bottomLeft;
		}
	}

	Mesh * mesh = new Mesh(vertices, verticesLength * sizeof(float), texCoords, texCoordsLength * sizeof(float), indices, indicesLength * sizeof(unsigned int), false);

	delete[] vertices;
	delete[] texCoords;
	delete[] indices;

	return mesh;
}

static float getInterpolatedHeightAt(float x, float z, int offXDeg, int offZDeg, float smallInc, float largeInc, unsigned long seed) {
	float minX = x - offXDeg * smallInc;
	float maxX = x + (SAMPLES_PER_UNIT - offXDeg) * smallInc;
	float minZ = z - offZDeg * smallInc;
	float maxZ = z + (SAMPLES_PER_UNIT - offZDeg) * smallInc;

	float bottomLeftHeight = getAverageHeightAt(minX, minZ, largeInc, seed);
	float bottomRightHeight = getAverageHeightAt(maxX, minZ, largeInc, seed);
	float topLeftHeight = getAverageHeightAt(minX, maxZ, largeInc, seed);
	float topRightHeight = getAverageHeightAt(maxX, maxZ, largeInc, seed);

	float temp1 = cosineInterpolation(bottomLeftHeight, bottomRightHeight, x - minX);
	float temp2 = cosineInterpolation(topLeftHeight, topRightHeight, x - minX);
	float interpolatedHeight = cosineInterpolation(temp1, temp2, z - minZ);

	return interpolatedHeight;
}

static float getAverageHeightAt(float x, float z, float inc, unsigned long seed) {
	const float cornerFactor = 0.05f;
	const float edgeFactor = 0.1f;
	const float centerFactor = 1 - cornerFactor * 4 - edgeFactor * 4;

	float bottomLeft = getHeightAt(x - inc, z - inc, seed);
	float bottomMiddle = getHeightAt(x, z - inc, seed);
	float bottomRight = getHeightAt(x + inc, z - inc, seed);
	float middleLeft = getHeightAt(x - inc, z, seed);
	float middleMiddle = getHeightAt(x, z, seed);
	float middleRight = getHeightAt(x + inc, z, seed);
	float topLeft = getHeightAt(x - inc, z + inc, seed);
	float topMiddle = getHeightAt(x, z + inc, seed);
	float topRight = getHeightAt(x + inc, z + inc, seed);

	float corners = (bottomLeft + bottomRight + topLeft + topRight) * cornerFactor;
	float edges = (bottomMiddle + middleLeft + middleRight + topMiddle) * edgeFactor;
	float center = middleMiddle * centerFactor;

	return corners + edges + center;
}

static float getHeightAt(float x, float z, unsigned long seed) {
	int pseudoSeed = (int)(x * 9081236803) + (int)(z * 3789548901) + seed;
	srand(pseudoSeed);
	return (float)rand() / RAND_MAX - 0.5f;
}