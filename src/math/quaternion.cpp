#include "quaternion.h"

Quaternion * Quaternion::vec3Mul(float vecX, float vecY, float vecZ) {
	float resX =  w * vecX + y * vecZ - z * vecY;
	float resY =  w * vecY + z * vecX - x * vecZ;
	float resZ =  w * vecZ + x * vecY - y * vecX;
	float resW = -x * vecX - y * vecY - z * vecZ;

	return new Quaternion(resX, resY, resZ, resW);
}

Quaternion * Quaternion::operator*(Quaternion &quat) {
	float newX =  x * quat.w + y * quat.z - z * quat.y + w * quat.x;
	float newY = -x * quat.z + y * quat.w + z * quat.x + w * quat.y;
	float newZ =  x * quat.y - y * quat.x + z * quat.w + w * quat.z;
	float newW = -x * quat.x - y * quat.y - z * quat.z + w * quat.w;

	return new Quaternion(newX, newY, newZ, newW);
}