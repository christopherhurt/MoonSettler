#pragma once

#include <math.h>
#include "math/mat4.h"
#include "math/trig.h"
#include "math/vec3.h"

Mat4 * genTransformationMatrix(float x, float y, float z, float rX, float rY, float rZ, float sX, float sY, float sZ);
Mat4 * genPerspectiveProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar);
Mat4 * genViewMatrix(Vec3 * pos, Vec3 * forward, Vec3 * up);