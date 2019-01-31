#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "rendering/shader.h"
#include "objects/cube.h"
#include "utils/matGen.h"

class Skybox {
public:
	Skybox(const char * textures[], Shader * shaderIn);
	void render();
	void setRotation(Vec3& rot);
	~Skybox();
private:
	unsigned int tex;
	unsigned int vao;
	unsigned int vertVbo;
	unsigned int ebo;
	Shader * shader;
};