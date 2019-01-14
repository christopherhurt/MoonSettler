#pragma once

#include "math/vec3.h"
#include "shader.h"

class Camera {
public:
	Camera(float xIn, float yIn, float zIn, Vec3 * forwardIn, Vec3 * upIn);
	void moveSide(float delta);
	void moveHeight(float delta);
	void moveDepth(float delta);
	void turnHorizontal(float theta);
	void turnVertical(float theta);
	void updateViewMatrix(Shader &shader);
	~Camera();
private:
	float x;
	float y;
	float z;
	Vec3 * forward;
	Vec3 * up;
};