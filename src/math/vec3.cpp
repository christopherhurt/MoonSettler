#include "vec3.h"

Vec3 * Vec3::cross(Vec3 &vec) {
	float cX = this->y * vec.z - this->z * vec.y;
	float cY = this->z * vec.x - this->x * vec.z;
	float cZ = this->x * vec.y - this->y * vec.x;

	return new Vec3(cX, cY, cZ);
}

Vec3 * Vec3::normalize() {
	double dX = (double)x;
	double dY = (double)y;
	double dZ = (double)z;
	float length = (float)sqrt(dX * dX + dY * dY + dZ * dZ);

	x /= length;
	y /= length;
	z /= length;

	return this;
}