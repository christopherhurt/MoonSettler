#include "camera.h"

Camera::Camera(Vec3 * posIn, Vec3 * forwardIn, Vec3 * upIn) : pos(posIn) {
	forward = forwardIn->normalize();
	up = upIn->normalize();
}

void Camera::moveSide(float delta) {
	Vec3 * right = forward->cross(*up);
	Vec3 * scaledRight = *right * delta;
	Vec3 * newPos = *pos + *scaledRight;

	delete pos;
	delete right;
	delete scaledRight;

	pos = newPos;
}

void Camera::moveHeight(float delta) {
	Vec3 * scaledUp = *up * delta;
	Vec3 * newPos = *pos + *scaledUp;

	delete pos;
	delete scaledUp;
	
	pos = newPos;
}

void Camera::moveDepth(float delta) {
	Vec3 * scaledForward = *forward * delta;
	Vec3 * newPos = *pos + *scaledForward;

	delete pos;
	delete scaledForward;

	pos = newPos;
}

void Camera::turnHorizontal(float theta) {
	// TODO
}

void Camera::turnVertical(float theta) {
	// TODO
}

void Camera::updateViewMatrix(Shader &shader) {
	Mat4 * viewMatrix = genViewMatrix(pos, forward, up);
	shader.setMat4("view", *viewMatrix);
	delete viewMatrix;
}

Camera::~Camera() {
	delete pos;
	delete forward;
	delete up;
}