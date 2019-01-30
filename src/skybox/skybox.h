#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "rendering/shader.h"

class Skybox {
public:
	Skybox(char * textures[]);
	void render();
	~Skybox();
private:
	Shader * shader;
};