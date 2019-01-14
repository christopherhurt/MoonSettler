#include "vec3.h"

Vec3 * Vec3::operator+(Vec3 &vec) {
	return new Vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

Vec3 * Vec3::operator*(float val) {
	return new Vec3(x * val, y * val, z * val);
}

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

void Vec3::rotate(Vec3 &axis, float theta) {
	float halfThetaRad = degToRad(theta) / 2;
	float sinHalfTheta = (float)sin(halfThetaRad);
	float cosHalfTheta = (float)cos(halfThetaRad);

	float rX = axis.x * sinHalfTheta;
	float rY = axis.y * sinHalfTheta;
	float rZ = axis.z * sinHalfTheta;
	float rW = cosHalfTheta;

	Quaternion * rotation = new Quaternion(rX, rY, rZ, rW);
	Quaternion * conjugate = rotation->conjugated();
	Quaternion * temp = rotation->vec3Mul(x, y, z);
	Quaternion * result = *temp * *conjugate;

	x = result->x;
	y = result->y;
	z = result->z;

	delete rotation;
	delete conjugate;
	delete temp;
	delete result;
}