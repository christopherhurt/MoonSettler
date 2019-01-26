#pragma once

#include "math/vec3.h"
#include "rendering/shader.h"

class Light {
public:
	inline Light(Vec3 * colorIn, float intensityIn) : color(colorIn), intensity(intensityIn) {}
	virtual void load(Shader &shader) = 0;
	inline Vec3 * getColor() { return color; }
	inline float getIntensity() { return intensity; }
private:
	Vec3 * color;
	float intensity;
};