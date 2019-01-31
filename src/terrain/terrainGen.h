#pragma once

#include <cstdlib>
#include <math.h>
#include "rendering/mesh.h"
#include "utils/interpolation.h"
#include "math/vec3.h"
#include "terrainFactors.h"

constexpr int CHUNK_WIDTH = CHUNK_SIZE - 1;
constexpr int SIDE_LENGTH = CHUNK_SIZE + (SAMPLES_PER_UNIT - 1) * CHUNK_WIDTH;
constexpr float INC = 1.0f / SAMPLES_PER_UNIT;

Mesh * genTerrainChunk(int chunkX, int chunkZ, unsigned long seed);
float getCompositeHeightAt(float x, float z, unsigned long seed);