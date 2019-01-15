#include "terrainGen.h"

constexpr unsigned int POINTS_PER_CHUNK = 4;
constexpr unsigned int SAMPLES_PER_UNIT = 4;
constexpr unsigned int OCTAVES = 3;
constexpr unsigned int SAMPLES_PER_UNIT_MULTIPLIER = 2;
constexpr unsigned int SIDE_LENGTH = POINTS_PER_CHUNK * SAMPLES_PER_UNIT - 1;
constexpr unsigned int VERTICES_SIZE = SIDE_LENGTH * SIDE_LENGTH * 3;
constexpr unsigned int TEX_COORDS_SIZE = SIDE_LENGTH * SIDE_LENGTH * 2;
constexpr unsigned int INDICES_SIZE = (SIDE_LENGTH - 1) * (SIDE_LENGTH - 1) * 6;
constexpr float CORNER_FACTOR = 0.05f;
constexpr float EDGE_FACTOR = 0.1f;
constexpr float CENTER_FACTOR = 1 - 4 * CORNER_FACTOR - 4 * EDGE_FACTOR;
constexpr float AMPLITUDE_DIVISOR = 4;
constexpr float LARGE_INC = 1.0f / (POINTS_PER_CHUNK - 1);
constexpr float SMALL_INC = LARGE_INC / (SAMPLES_PER_UNIT - 1);

static float * genGrid(int chunkX, int chunkZ, unsigned long seed);
static float calcAverageHeight(float x, float z, float inc, unsigned long seed);
static float getHeightAt(float x, float z, unsigned long seed);
static float * genTexCoords();
static unsigned int * genIndices();

Mesh * genTerrainChunk(int chunkX, int chunkZ, unsigned long seed) {
	float * vertices = genGrid(chunkX, chunkZ, seed);
	float * texCoords = genTexCoords();
	unsigned int * indices = genIndices();

	Mesh * chunkMesh = new Mesh(vertices, VERTICES_SIZE * sizeof(float), texCoords, TEX_COORDS_SIZE * sizeof(float), indices, INDICES_SIZE * sizeof(unsigned int));

	delete[] vertices;
	delete[] texCoords;
	delete[] indices;

	return chunkMesh;
}

static float * genGrid(int chunkX, int chunkZ, unsigned long seed) {
	float * vertices = new float[VERTICES_SIZE];
	float baseX = chunkX - 0.5f;
	float baseZ = chunkZ - 0.5f;
	
	for (int zIndex = 0; zIndex < POINTS_PER_CHUNK; zIndex++) {
		for (int xIndex = 0; xIndex < POINTS_PER_CHUNK; xIndex++) {
			float floorX = baseX + xIndex * LARGE_INC;
			float ceilX = baseX + (xIndex + 1) * LARGE_INC;
			float floorZ = baseZ + zIndex * LARGE_INC;
			float ceilZ = baseZ + (zIndex + 1) * LARGE_INC;

			float bottomLeftY = calcAverageHeight(floorX, floorZ, LARGE_INC, seed);
			float bottomRightY = calcAverageHeight(ceilX, floorZ, LARGE_INC, seed);
			float topLeftY = calcAverageHeight(floorX, ceilZ, LARGE_INC, seed);
			float topRightY = calcAverageHeight(ceilX, ceilZ, LARGE_INC, seed);

			for (int sampleIndexZ = 0; sampleIndexZ < SAMPLES_PER_UNIT; sampleIndexZ++) {
				for (int sampleIndexX = 0; sampleIndexX < SAMPLES_PER_UNIT; sampleIndexX++) {
					float x = floorX + sampleIndexX * SMALL_INC;
					float z = floorZ + sampleIndexZ * SMALL_INC;
					
					float sampleOffsetX = x - floorX;
					float sampleOffsetZ = z - floorZ;
					float temp1 = cosineInterpolation(bottomLeftY, bottomRightY, sampleOffsetX);
					float temp2 = cosineInterpolation(topLeftY, topRightY, sampleOffsetX);
					float y = cosineInterpolation(temp1, temp2, sampleOffsetZ);

					int vertexIndex = (zIndex * POINTS_PER_CHUNK * SAMPLES_PER_UNIT) + (xIndex * SAMPLES_PER_UNIT) + (sampleIndexZ * SAMPLES_PER_UNIT) + sampleIndexX;
					int xOff = vertexIndex * 3;
					int yOff = xOff + 1;
					int zOff = xOff + 2;

					*(vertices + xOff) = x;
					*(vertices + yOff) = y;
					*(vertices + zOff) = z;
				}
			}
		}
	}

	return vertices;
}

static float calcAverageHeight(float x, float z, float inc, unsigned long seed) {
	float bottomLeft = getHeightAt(x - inc, z - inc, seed);
	float bottomMiddle = getHeightAt(x, z - inc, seed);
	float bottomRight = getHeightAt(x + inc, z - inc, seed);
	float middleLeft = getHeightAt(x - inc, z, seed);
	float middleMiddle = getHeightAt(x, z, seed);
	float middleRight = getHeightAt(x + inc, z, seed);
	float topLeft = getHeightAt(x - inc, z + inc, seed);
	float topMiddle = getHeightAt(x, z + inc, seed);
	float topRight = getHeightAt(x + inc, z + inc, seed);

	float corners = (bottomLeft + bottomRight + topLeft + topRight) * CORNER_FACTOR;
	float edges = (bottomMiddle + middleLeft + middleRight + topMiddle) * EDGE_FACTOR;
	float center = middleMiddle * CENTER_FACTOR;

	return corners + edges + center;
}

static float getHeightAt(float x, float z, unsigned long seed) {
	unsigned int pseudoSeed = (unsigned int)(x * 8934769492) + (unsigned int)(z * 6294609218) + seed;
	srand(pseudoSeed);
	return (float)rand() / RAND_MAX - 0.5f;
}

static float * genTexCoords() {
	float * texCoords = new float[TEX_COORDS_SIZE];

	for (int i = 0; i < SIDE_LENGTH; i++) {
		for (int j = 0; j < SIDE_LENGTH; j++) {
			float u = j * SMALL_INC;
			float v = i * SMALL_INC;

			int index = i * SIDE_LENGTH + j;
			int uOff = index * 2;
			int vOff = uOff + 1;

			*(texCoords + uOff) = u;
			*(texCoords + vOff) = v;
		}
	}
	
	return texCoords;
}

static unsigned int * genIndices() {
	unsigned int * indices = new unsigned int[INDICES_SIZE];

	for (int i = 0; i < SIDE_LENGTH - 1; i++) {
		for (int j = 0; j < SIDE_LENGTH - 1; j++) {
			unsigned int index0 = i * SIDE_LENGTH + j;
			unsigned int index1 = index0 + SIDE_LENGTH;
			unsigned int index2 = index1 + 1;
			unsigned int index3 = index0 + 1;

			unsigned int off0 = (i * (SIDE_LENGTH - 1) + j) * 6;
			unsigned int off1 = off0 + 1;
			unsigned int off2 = off0 + 2;
			unsigned int off3 = off0 + 3;
			unsigned int off4 = off0 + 4;
			unsigned int off5 = off0 + 5;

			*(indices + off0) = index0;
			*(indices + off1) = index1;
			*(indices + off2) = index2;
			*(indices + off3) = index2;
			*(indices + off4) = index3;
			*(indices + off5) = index0;
		}
	}

	return indices;
}