#include "camera.h"

Camera::Camera(Vec3 * posIn, Vec3 * forwardIn, Vec3 * upIn) : pos(posIn) {
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
	delete pos;
	delete forward;
	delete up;
}