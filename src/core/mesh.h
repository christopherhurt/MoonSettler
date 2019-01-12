#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

class Mesh {
public:
	Mesh(const float vertices[], const unsigned int verticesLength, const unsigned int indices[], const unsigned int indicesLength);
	void bind();
	~Mesh();
private:
	unsigned int vao;
	unsigned int vertVbo;
	unsigned int indEbo;
};