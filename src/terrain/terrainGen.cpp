#include "terrainGen.h"

static constexpr float CENTER_AVERAGE_FACTOR = 1 - 4 * (CORNER_AVERAGE_FACTOR + EDGE_AVERAGE_FACTOR);
static constexpr int HALF_INT_MAX = INT_MAX / 2;

static Vec3 * getNormalVectorAt(float x, float z, unsigned long seed);
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
	for (float currZ = 0; currZ <= CHUNK_WIDTH; currZ += INC) {
		for(float currX = 0; currX <= CHUNK_WIDTH; currX += INC) {
			float texU = (float)currX / CHUNK_WIDTH;
			float texV = (float)currZ / CHUNK_WIDTH;

			float vertX = (float)(currX + chunkX * CHUNK_WIDTH);
			float vertZ = (float)(currZ + chunkZ * CHUNK_WIDTH);
			float vertY = getCompositeHeightAt(vertX, vertZ, seed);
			
			vertices[index * 3] = vertX;
			vertices[index * 3 + 1] = vertY;
			vertices[index * 3 + 2] = vertZ;

			Vec3 * normal = getNormalVectorAt(vertX, vertZ, seed);
			normals[index * 3] = normal->x;
			normals[index * 3 + 1] = normal->y;
			normals[index * 3 + 2] = normal->z;
			delete normal;

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

float getCompositeHeightAt(float x, float z, unsigned long seed) {
	float height = 0;
	float amplitude = 1;
	float frequency = 1;
	for (int i = 0; i < OCTAVES; i++) {
		height += getInterpolatedHeightAt(x * frequency, z * frequency, seed) * amplitude;
		amplitude *= AMPLITUDE_MULTIPLIER;
		frequency *= FREQUENCY_MULTIPLIER;
	}

	return height;
}

static Vec3 * getNormalVectorAt(float x, float z, unsigned long seed) {
	float leftHeight = getCompositeHeightAt(x - 1, z, seed);
	float rightHeight = getCompositeHeightAt(x + 1, z, seed);
	float bottomHeight = getCompositeHeightAt(x, z - 1, seed);
	float topHeight = getCompositeHeightAt(x, z + 1, seed);

	Vec3 * normal = new Vec3(leftHeight - rightHeight, 2.0f, bottomHeight - topHeight);
	normal->normalize();

	return normal;
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
	float totalHeight = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			float currHeight = getHeightAt(x + i, z + j, seed);

			if (i == 0 && j == 0) {
				totalHeight += currHeight * CENTER_AVERAGE_FACTOR;
			}
			else if (i != 0 && j != 0) {
				totalHeight += currHeight * CORNER_AVERAGE_FACTOR;
			}
			else {
				totalHeight += currHeight * EDGE_AVERAGE_FACTOR;
			}
		}
	}

	return totalHeight;
}

static float getHeightAt(float x, float z, unsigned long seed) {
	srand(seed);
	unsigned int tempSeed = (unsigned int)(x * rand() / 2 + HALF_INT_MAX);
	srand(tempSeed);
	unsigned int pseudoSeed = (unsigned int)(z * rand() / 2 + HALF_INT_MAX);
	srand(pseudoSeed);
	return (float)rand() / RAND_MAX - 0.5f;
}