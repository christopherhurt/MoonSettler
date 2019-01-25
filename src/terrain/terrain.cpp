#include "terrain.h"

static Chunk * getChunkAt(int x, int z, list<Chunk *> * chunks);

Terrain::Terrain(float scaleIn, float amplitudeIn, Shader * shaderIn, Camera * camIn, Material * materialIn, unsigned long seedIn) : scale(scaleIn), amplitude(amplitudeIn), shader(shaderIn), cam(camIn), material(materialIn), seed(seedIn) {
	chunks = new list<Chunk *>();
}

void Terrain::updateAndRender() {
	material->loadAndBind(*shader);
	Vec3 * playerPos = cam->getPos();
	
	int playerChunkX = (int)floor(-playerPos->x / scale / CHUNK_WIDTH);
	int playerChunkZ = (int)floor(playerPos->z / scale / CHUNK_WIDTH);

	int minChunkX = playerChunkX - VIEW_DISTANCE;
	int maxChunkX = playerChunkX + VIEW_DISTANCE;
	int minChunkZ = playerChunkZ - VIEW_DISTANCE;
	int maxChunkZ = playerChunkZ + VIEW_DISTANCE;

	for (int currChunkZ = minChunkZ; currChunkZ <= maxChunkZ; currChunkZ++) {
		for (int currChunkX = minChunkX; currChunkX <= maxChunkX; currChunkX++) {
			Chunk * currChunk;
			if ((currChunk = getChunkAt(currChunkX, currChunkZ, chunks)) == nullptr) {
				currChunk = new Chunk(currChunkX, currChunkZ, scale, amplitude, seed);
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