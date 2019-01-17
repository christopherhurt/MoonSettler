#include "chunk.h"

Chunk::Chunk(int xIn, int zIn, float scale, float amplitude, unsigned long seed) : x(xIn), z(zIn) {
	mesh = genTerrainChunk(x, z, seed);
	transform = genTransformationMatrix(0, 0, 0, 0, 0, 0, scale, amplitude, scale);
}

void Chunk::render(Shader * shader) {
	shader->setMat4("transform", *transform);
	mesh->bind();
	glDrawElements(GL_TRIANGLES, mesh->getNumIndices(), GL_UNSIGNED_INT, 0);
}

Chunk::~Chunk() {
	delete mesh;
	delete transform;
}