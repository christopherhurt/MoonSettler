#include "directionalLight.h"

void DirectionalLight::load(Shader &shader) {
	shader.setVec3("directionalLight.basic.color", *getColor());
	shader.setFloat("directionalLight.basic.intensity", getIntensity());

	shader.setVec3("directionalLight.direction", *direction);
}

DirectionalLight::~DirectionalLight() {
	delete getColor();
	delete direction;
}