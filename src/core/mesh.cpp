#include "mesh.h"

Mesh::Mesh(const float vertices[], const unsigned int verticesLength, const unsigned int indices[], const unsigned int indicesLength) {
	vao = 0;
	vertVbo = 0;
	indEbo = 0;

	// Vertex VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex VBO
	glGenBuffers(1, &vertVbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesLength, vertices, GL_STATIC_DRAW);

	// Element buffer object
	glGenBuffers(1, &indEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesLength, indices, GL_STATIC_DRAW);

	// Set up attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// Unbinding
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::bind() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vertVbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indEbo);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &indEbo);
	glDeleteBuffers(1, &vertVbo);
	glDeleteVertexArrays(1, &vao);
}