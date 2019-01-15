#pragma once

#include <cstdlib>
#include "core/mesh.h"
#include "utils/interpolation.h"

constexpr float INTERPOLATION_FACTOR = 0.5f;
constexpr float CORNER_FACTOR = 0.05f;
constexpr float EDGE_FACTOR = 0.1f;
constexpr float CENTER_FACTOR = 1 - 4 * CORNER_FACTOR - 4 * EDGE_FACTOR;
constexpr float ROUGNESS = 0.25f;
constexpr unsigned int POINTS_PER_CHUNK = 4;
constexpr unsigned int SAMPLES_PER_UNIT = 8;
constexpr unsigned int OCTAVES = 3;
constexpr unsigned int FREQUENCY_DIVISOR = 2;

Mesh * genTerrainChunk(int chunkX, int chunkZ, unsigned long seed);