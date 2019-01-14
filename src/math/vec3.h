#pragma once

#include "math.h"

class Vec3 {
public:
	float x;
	float y;
	float z;
	inline Vec3(float xIn, float yIn, float zIn) : x(xIn), y(yIn), z(zIn) {}
	Vec3 * operator+(Vec3 &vec);
	Vec3 * operator*(float val);
	Vec3 * cross(Vec3 &vec);
	Vec3 * normalize();
};