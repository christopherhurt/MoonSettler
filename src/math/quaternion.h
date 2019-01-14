#pragma once

class Quaternion {
public:
	float x;
	float y;
	float z;
	float w;

	inline Quaternion(float xIn, float yIn, float zIn, float wIn) : x(xIn), y(yIn), z(zIn), w(wIn) {}
	inline Quaternion * conjugated() { return new Quaternion(-x, -y, -z, w); }
	Quaternion * vec3Mul(float vecX, float vecY, float vecZ);
	Quaternion * operator*(Quaternion &quat);
};