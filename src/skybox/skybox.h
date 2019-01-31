#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "rendering/shader.h"
#include "objects/cube.h"

class Skybox {
public:
	Skybox(const char * textures[]);
	void render();
	~Skybox();
private:
	unsigned int tex;
	unsigned int vao;
	unsigned int vertVbo;
	unsigned int ebo;
};