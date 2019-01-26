#pragma once

#include "light.h"
#include "rendering/shader.h"

class DirectionalLight : public Light {
public:
	inline DirectionalLight(Vec3 * color, float intensity, Vec3 * directionIn) : Light(color, intensity), direction(directionIn) {}
	virtual void load(Shader &shader);
	inline Vec3 * getDirection() { return direction; }
	~DirectionalLight();
private:
	Vec3 * direction;
};