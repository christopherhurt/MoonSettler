#pragma once

#include <math.h>
#include "math/mat4.h"
#include "math/pi.h"

Mat4 * genTransformationMatrix(float x, float y, float z, float rX, float rY, float rZ, float sX, float sY, float sZ);