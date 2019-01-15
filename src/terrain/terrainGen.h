#pragma once

#include <cstdlib>
#include <math.h>
#include "core/mesh.h"
#include "utils/interpolation.h"

Mesh * genTerrainChunk(int chunkX, int chunkZ, unsigned long seed);