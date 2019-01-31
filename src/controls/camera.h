#pragma once

#include "math/vec3.h"
#include "rendering/shader.h"
#include "utils/matGen.h"

constexpr float HEAD_HEIGHT = 3;

class Camera {
public:
	Camera(Vec3 * pos, Vec3 * forwardIn, Vec3 * upIn);
	void moveSide(float delta);
	void moveHeight(float delta);
	void moveDepth(float delta);
	void turnHorizontal(float theta);
	void turnVertical(float theta);
	Mat4 * constructViewMatrix();
	inline void setHeight(float height) { pos->y = height; }
	inline Vec3 * getPos() { return pos; }
	~Camera();
private:
	Vec3 * pos;
	Vec3 * forward;
	Vec3 * up;
};