#include "camera.h"

Camera::Camera(float xIn, float yIn, float zIn, Vec3 * forwardIn, Vec3 * upIn) : x(xIn), y(yIn), z(zIn) {
	forward = forwardIn->normalize();
	up = upIn->normalize();
}

void Camera::moveSide(float delta) {
	// TODO
}

void Camera::moveHeight(float delta) {
	// TODO
}

void Camera::moveDepth(float delta) {
	// TODO
}

void Camera::turnHorizontal(float theta) {
	// TODO
}

void Camera::turnVertical(float theta) {
	// TODO
}

void Camera::updateViewMatrix(Shader &shader) {
	// TODO
}

Camera::~Camera() {
	delete forward;
	delete up;
}