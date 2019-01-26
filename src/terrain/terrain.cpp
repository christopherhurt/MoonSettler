#include "terrain.h"

// TODO: remove
#include <iostream>
using namespace std;

static constexpr float CEIL_OFFSET = 0.000001f;

static Chunk * getChunkAt(int x, int z, list<Chunk *> * chunks);
static float interpolateTriangleHeight(Vec3& t1, Vec3& t2, Vec3& t3, float x, float z);

Terrain::Terrain(Shader * shaderIn, Camera * camIn, Material * materialIn, unsigned long seedIn) : shader(shaderIn), cam(camIn), material(materialIn), seed(seedIn) {
	chunks = new list<Chunk *>();
}

void Terrain::updateAndRender() {
	material->loadAndBind(*shader);
	Vec3 * playerPos = cam->getPos();
	
	int playerChunkX = (int)floor(playerPos->x / TERRAIN_SCALE / CHUNK_WIDTH);
	int playerChunkZ = (int)floor(playerPos->z / TERRAIN_SCALE / CHUNK_WIDTH);

	int minChunkX = playerChunkX - VIEW_DISTANCE;
	int maxChunkX = playerChunkX + VIEW_DISTANCE;
	int minChunkZ = playerChunkZ - VIEW_DISTANCE;
	int maxChunkZ = playerChunkZ + VIEW_DISTANCE;

	for (int currChunkZ = minChunkZ; currChunkZ <= maxChunkZ; currChunkZ++) {
		for (int currChunkX = minChunkX; currChunkX <= maxChunkX; currChunkX++) {
			Chunk * currChunk;
			if ((currChunk = getChunkAt(currChunkX, currChunkZ, chunks)) == nullptr) {
				currChunk = new Chunk(currChunkX, currChunkZ, TERRAIN_SCALE, TERRAIN_AMPLITUDE, seed);
				chunks->push_front(currChunk);
				
				if (chunks->size() > MAX_CHUNKS_LOADED) {
					chunks->pop_back();
				}
			}

			currChunk->render(shader);
		}
	}

	unbindBuffers();
	unbindTexture(0);
}

float Terrain::getPlayerHeightAt(float x, float z) {
	float downscaledX = x / TERRAIN_SCALE;
	float downscaledZ = z / TERRAIN_SCALE;

	float xLow = floor(downscaledX * SAMPLES_PER_UNIT) / SAMPLES_PER_UNIT;
	float xHigh = ceil(downscaledX * SAMPLES_PER_UNIT + CEIL_OFFSET) / SAMPLES_PER_UNIT;
	float zLow = floor(downscaledZ * SAMPLES_PER_UNIT) / SAMPLES_PER_UNIT;
	float zHigh = ceil(downscaledZ * SAMPLES_PER_UNIT + CEIL_OFFSET) / SAMPLES_PER_UNIT;

	// TODO: debugging
	cout << "x: " << x << "\nz: " << z << endl;
	cout << "xLow: " << xLow << "\nxHigh: " << xHigh << "\nzLow: " << zLow << "\nzHigh: " << zHigh << endl << endl;

	Vec3 t1(xLow, getCompositeHeightAt(xLow, zLow, seed), zLow);
	Vec3 t2(0, 0, 0);
	Vec3 t3(xHigh, getCompositeHeightAt(xHigh, zHigh, seed), zHigh);
	
	float relX = x - xLow;
	float relZ = z - zLow;

	if (relZ < relX) {
		t2.x = xHigh;
		t2.y = getCompositeHeightAt(xHigh, zLow, seed);
		t2.z = zLow;
	}
	else {
		t2.x = xLow;
		t2.y = getCompositeHeightAt(xLow, zHigh, seed);
		t2.z = zHigh;
	}

	// TODO
	cout << "t1 height: " << t1.y << endl;
	cout << "t2 height: " << t2.y << endl;
	cout << "t3 height: " << t3.y << endl;

	// TODO: fix bumpiness in height while moving
	float playerHeight = interpolateTriangleHeight(t1, t2, t3, downscaledX, downscaledZ) * TERRAIN_AMPLITUDE + HEAD_HEIGHT;
	//float playerHeight = getCompositeHeightAt(downscaledX, downscaledZ, seed) * TERRAIN_AMPLITUDE + HEAD_HEIGHT;

	// TODO
	cout << "Base player height: " << playerHeight << endl << endl;

	return playerHeight;
}

Terrain::~Terrain() {
	delete material;
	delete chunks;
}

static Chunk * getChunkAt(int x, int z, list<Chunk *> * chunks) {
	for (list<Chunk *>::iterator iter = chunks->begin(); iter != chunks->end(); ++iter) {
		Chunk * chunk = *iter;

		if (chunk->getX() == x && chunk->getZ() == z) {
			return chunk;
		}
	}

	return nullptr;
}

static float interpolateTriangleHeight(Vec3& t1, Vec3& t2, Vec3& t3, float x, float z) {
	float determinant = (t2.z - t3.z) * (t1.x - t3.x) + (t3.x - t2.x) * (t1.z - t3.z);

	float f1 = ((t2.z - t3.z) * (x - t3.x) + (t3.x - t2.x) * (z - t3.z)) / determinant;
	float f2 = ((t3.z - t1.z) * (x - t3.x) + (t1.x - t3.x) * (z - t3.z)) / determinant;
	float f3 = 1 - f2 - f1;

	float height = f1 * t1.y + f2 * t2.y + f3 * t3.y;
	return height;
}