#include "camera.h"

Camera::Camera(Vec3 * posIn, Vec3 * forwardIn, Vec3 * upIn) : pos(posIn) {
	forward = forwardIn->normalize();
	up = upIn->normalize();
}

void Camera::moveSide(float delta) {
	Vec3 * right = forward->cross(*up);
	Vec3 * scaledRight = *right * -delta;
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
	Vec3 * Y_AXIS = new Vec3(0, 1, 0);
	Vec3 * horiz = Y_AXIS->cross(*forward);
	horiz->normalize();

	forward->rotate(*Y_AXIS, -theta);
	forward->normalize();

	Vec3 * newUp = forward->cross(*horiz);
	delete up;
	up = newUp;
	up->normalize();

	delete Y_AXIS;
	delete horiz;
}

void Camera::turnVertical(float theta) {
	Vec3 * Y_AXIS = new Vec3(0, 1, 0);
	Vec3 * horiz = Y_AXIS->cross(*forward);
	horiz->normalize();

	forward->rotate(*horiz, theta);
	forward->normalize();

	Vec3 * newUp = forward->cross(*horiz);
	delete up;
	up = newUp;
	up->normalize();

	delete Y_AXIS;
	delete horiz;
}

void Camera::update(Shader &shader) {
	Mat4 * viewMatrix = genViewMatrix(pos, forward, up);
	shader.setMat4("view", *viewMatrix);
	delete viewMatrix;

	shader.setVec3("camLoc", *getPos());
}

Camera::~Camera() {
	delete pos;
	delete forward;
	delete up;
}