#pragma once

#include <math.h>
#include "math/trig.h"
#include "quaternion.h"

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
	float length();
	float dot(Vec3 &vec);
	float angleBetween(Vec3 &vec);
	void rotate(Vec3 &axis, float theta);
};