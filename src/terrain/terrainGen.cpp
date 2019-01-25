#include "terrainGen.h"

static float getInterpolatedHeightAt(float x, float z, unsigned long seed);
static float getAverageHeightAt(float x, float z, unsigned long seed);
static float getHeightAt(float x, float z, unsigned long seed);

Mesh * genTerrainChunk(int chunkX, int chunkZ, unsigned long seed) {
	unsigned int verticesLength = SIDE_LENGTH * SIDE_LENGTH * 3;
	unsigned int texCoordsLength = SIDE_LENGTH * SIDE_LENGTH * 2;
	unsigned int normalsLength = verticesLength;
	unsigned int indicesLength = (SIDE_LENGTH - 1) * (SIDE_LENGTH - 1) * 6;

	float * vertices = new float[verticesLength];
	float * texCoords = new float[texCoordsLength];
	float * normals = new float[normalsLength];
	unsigned int * indices = new unsigned int[indicesLength];

	int index = 0;
	for (float currZ = 0; currZ <= CHUNK_SIZE - 1; currZ += INC) {
		for(float currX = 0; currX <= CHUNK_SIZE - 1; currX += INC) {
			float texU = (float)currX / (CHUNK_SIZE - 1);
			float texV = (float)currZ / (CHUNK_SIZE - 1);

			float vertX = (float)(currX + chunkX * (CHUNK_SIZE - 1));
			float vertZ = (float)(currZ + chunkZ * (CHUNK_SIZE - 1));

			float vertY = 0;
			float amplitude = 1;
			float frequency = 1;
			for (int i = 0; i < OCTAVES; i++) {
				vertY += getInterpolatedHeightAt(vertX * frequency, vertZ * frequency, seed) * amplitude;
				amplitude *= AMPLITUDE_MULTIPLIER;
				frequency *= FREQUENCY_MULTIPLIER;
			}
			
			vertices[index * 3] = vertX;
			vertices[index * 3 + 1] = vertY;
			vertices[index * 3 + 2] = vertZ;

			// TODO: change these
			normals[index * 3] = 0;
			normals[index * 3 + 1] = 1;
			normals[index * 3 + 2] = 0;

			texCoords[index * 2] = texU;
			texCoords[index * 2 + 1] = texV;

			index++;
		}
	}

	index = 0;
	for (int blockZ = 0; blockZ < SIDE_LENGTH - 1; blockZ++) {
		for (int blockX = 0; blockX < SIDE_LENGTH - 1; blockX++) {
			int bottomLeft = blockZ * SIDE_LENGTH + blockX;
			int topLeft = (blockZ + 1) * SIDE_LENGTH + blockX;
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

	Mesh * mesh = new Mesh(vertices, verticesLength * sizeof(float), texCoords, texCoordsLength * sizeof(float), normals, normalsLength * sizeof(float), indices, indicesLength * sizeof(unsigned int), false);

	delete[] vertices;
	delete[] texCoords;
	delete[] normals;
	delete[] indices;

	return mesh;
}

static float getInterpolatedHeightAt(float x, float z, unsigned long seed) {
	float minX = (float)floor(x);
	float maxX = (float)ceil(x);
	float minZ = (float)floor(z);
	float maxZ = (float)ceil(z);

	float bottomLeftHeight = getAverageHeightAt(minX, minZ, seed);
	float bottomRightHeight = getAverageHeightAt(maxX, minZ, seed);
	float topLeftHeight = getAverageHeightAt(minX, maxZ, seed);
	float topRightHeight = getAverageHeightAt(maxX, maxZ, seed);

	float amtX = x - minX;
	float amtZ = z - minZ;

	float temp1 = cosineInterpolation(bottomLeftHeight, bottomRightHeight, amtX);
	float temp2 = cosineInterpolation(topLeftHeight, topRightHeight, amtX);
	float interpolatedHeight = cosineInterpolation(temp1, temp2, amtZ);

	return interpolatedHeight;
}

static float getAverageHeightAt(float x, float z, unsigned long seed) {
	const float cornerFactor = 0.05f;
	const float edgeFactor = 0.1f;
	const float centerFactor = 1 - cornerFactor * 4 - edgeFactor * 4;

	float totalHeight = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			float currHeight = getHeightAt(x + i, z + j, seed);

			if (i == 0 && j == 0) {
				totalHeight += currHeight * centerFactor;
			}
			else if (i != 0 && j != 0) {
				totalHeight += currHeight * cornerFactor;
			}
			else {
				totalHeight += currHeight * edgeFactor;
			}
		}
	}

	return totalHeight;
}

static float getHeightAt(float x, float z, unsigned long seed) {
	int pseudoSeed = (int)(x * 833433) * (int)(z * 743301) + seed;
	srand(pseudoSeed);
	return (float)rand() / RAND_MAX - 0.5f;
}