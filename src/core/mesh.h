#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh {
public:
	Mesh(const float vertices[], const unsigned int verticesLength, const float texCoords[], const unsigned int texCoordsLength, const unsigned int indices[], const unsigned int indicesLength);
	void bind();
	~Mesh();
private:
	unsigned int vao;
	unsigned int vertVbo;
	unsigned int texVbo;
	unsigned int indEbo;
};