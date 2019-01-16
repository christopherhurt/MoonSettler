#include "terrainGen.h"

// TODO
#include <iostream>
using namespace std;

static constexpr unsigned int POINTS_PER_SIDE = 10;
static constexpr unsigned int SAMPLES_PER_UNIT = 20;
static constexpr unsigned int VERTICES_PER_SIDE = POINTS_PER_SIDE + (SAMPLES_PER_UNIT - 1) * (POINTS_PER_SIDE - 1);
static constexpr float SMALL_INC = 1 / (VERTICES_PER_SIDE - 1.0f);
static constexpr float LARGE_INC = 1 / (POINTS_PER_SIDE - 1.0f);

static float getInterpolatedHeightAt(float x, float z, int offXDeg, int offZDeg, float smallInc, float largeInc, unsigned long seed);
static float getAverageHeightAt(float x, float z, float inc, unsigned long seed);
static float getHeightAt(float x, float z, unsigned long seed);

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
				//cout << "Averaging..." << endl; // TODO
				vertY = getAverageHeightAt(vertX, vertZ, LARGE_INC, seed);
			}
			else {
				//cout << "Interpolating..." << endl; // TODO
				vertY = getInterpolatedHeightAt(vertX, vertZ, SAMPLES_PER_UNIT - offXDeg, offZDeg, SMALL_INC, LARGE_INC, seed); // TODO
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

	// TODO
	/*cout << "Large inc: " << largeInc << endl;
	cout << "Small inc: " << smallInc << endl;
	cout << "Off X Degree: " << offXDeg << endl;
	cout << "Off Z Degree: " << offZDeg << endl;
	cout << "This X: " << x << endl;
	cout << "This Z: " << z << endl;
	cout << "Min X: " << minX << endl;
	cout << "Max X: " << maxX << endl;
	cout << "Min Z: " << minZ << endl;
	cout << "Max Z: " << maxZ << endl;*/

	float bottomLeftHeight = getAverageHeightAt(minX, minZ, largeInc, seed);
	float bottomRightHeight = getAverageHeightAt(maxX, minZ, largeInc, seed);
	float topLeftHeight = getAverageHeightAt(minX, maxZ, largeInc, seed);
	float topRightHeight = getAverageHeightAt(maxX, maxZ, largeInc, seed);

	// TODO
	//cout << "Factor X: " << (x - minX) / largeInc << endl;
	//cout << "Factor Z: " << (z - minZ) / largeInc << endl;

	/*cout << "Bottom left height: " << bottomLeftHeight << endl;
	cout << "Bottom right height: " << bottomRightHeight << endl;
	cout << "Top left height: " << topLeftHeight << endl;
	cout << "Top right height: " << topRightHeight << endl << endl;*/

	float temp1 = cosineInterpolation(bottomLeftHeight, bottomRightHeight, (x - minX) / largeInc); // TODO: amt value
	float temp2 = cosineInterpolation(topLeftHeight, topRightHeight, (x - minX) / largeInc);
	float interpolatedHeight = cosineInterpolation(temp1, temp2, (z - minZ) / largeInc);
	//float fac1 = (x - minX) / largeInc;
	//float temp1 = bottomLeftHeight * (1 - fac1) + bottomRightHeight * fac1;
	//float temp2 = topLeftHeight * (1 - fac1) + topRightHeight * fac1;
	//float fac2 = (z - minZ) / largeInc;
	//float interpolatedHeight = temp1 * (1 - fac2) + temp2 * fac2; // TODO

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
	int pseudoSeed = (int)(x * 81383503) + (int)(z * 743854901) + seed;
	srand(pseudoSeed);
	return ((float)rand() / RAND_MAX - 0.5f);
}