#pragma once

#include "light.h"
#include "core/shader.h"

class DirectionalLight : Light {
public:
	inline DirectionalLight(Vec3 * color, float intensity, Vec3 * directionIn) : Light(color, intensity), direction(directionIn) {}
	virtual void load(Shader &shader);
	~DirectionalLight();
private:
	Vec3 * direction;
};