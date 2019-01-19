#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh {
public:
	Mesh(const float vertices[], const unsigned int verticesSize, const float texCoords[], const unsigned int texCoordsSize, const float normals[], const unsigned int normalsSize, const unsigned int indices[], const unsigned int indicesSize, bool drawStripIn);
	void bind();
	inline unsigned int getNumIndices() { return numIndices; }
	inline bool shouldDrawStrip() { return drawStrip; }
	~Mesh();
private:
	unsigned int vao;
	unsigned int vertVbo;
	unsigned int texVbo;
	unsigned int normVbo;
	unsigned int indEbo;
	unsigned int numIndices;
	bool drawStrip;
};