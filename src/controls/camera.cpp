#include "camera.h"

static Vec3 Y_AXIS(0, 1, 0);

Camera::Camera(Vec3 * posIn, Vec3 * forwardIn, Vec3 * upIn) : pos(posIn) {
	forward = forwardIn->normalize();
	up = upIn->normalize();
}

void Camera::moveSide(float delta) {
	Vec3 forward2D(forward->x, 0, forward->z);
	forward2D.normalize();

	Vec3 * right = forward2D.cross(Y_AXIS);
	right->normalize();
	Vec3 * scaledRight = *right * -delta;
	Vec3 * newPos = *pos + *scaledRight;

	delete pos;
	delete right;
	delete scaledRight;

	pos = newPos;
}

void Camera::moveHeight(float delta) {
	Vec3 * scaledUp = Y_AXIS * delta;
	Vec3 * newPos = *pos + *scaledUp;

	delete pos;
	delete scaledUp;
	
	pos = newPos;
}

void Camera::moveDepth(float delta) {
	Vec3 forward2D(forward->x, 0, forward->z);
	forward2D.normalize();

	Vec3 * scaledForward = forward2D * delta;
	Vec3 * newPos = *pos + *scaledForward;

	delete pos;
	delete scaledForward;

	pos = newPos;
}

void Camera::turnHorizontal(float theta) {
	Vec3 * horiz = Y_AXIS.cross(*forward);
	horiz->normalize();

	forward->rotate(Y_AXIS, -theta);
	forward->normalize();

	Vec3 * newUp = forward->cross(*horiz);
	delete up;
	up = newUp;
	up->normalize();

	delete horiz;
}

void Camera::turnVertical(float theta) {
	Vec3 * horiz = Y_AXIS.cross(*forward);
	horiz->normalize();

	forward->rotate(*horiz, theta);
	forward->normalize();

	Vec3 * newUp = forward->cross(*horiz);
	delete up;
	up = newUp;
	up->normalize();

	delete horiz;
}

Mat4 * Camera::constructViewMatrix() {
	return genViewMatrix(pos, forward, up);
}

Camera::~Camera() {
	delete pos;
	delete forward;
	delete up;
}