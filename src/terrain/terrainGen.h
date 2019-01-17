#pragma once

#include <cstdlib>
#include <math.h>
#include "core/mesh.h"
#include "utils/interpolation.h"

constexpr int CHUNK_SIZE = 4;
constexpr int SAMPLES_PER_UNIT = 8;
constexpr int OCTAVES = 3;
constexpr float AMPLITUDE_MULTIPLIER = 0.4f;
constexpr float FREQUENCY_MULTIPLIER = 2;

constexpr int SIDE_LENGTH = CHUNK_SIZE + (SAMPLES_PER_UNIT - 1) * (CHUNK_SIZE - 1);
constexpr float INC = 1.0f / SAMPLES_PER_UNIT;

Mesh * genTerrainChunk(int chunkX, int chunkZ, unsigned long seed);