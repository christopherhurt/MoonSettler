#include "mesh.h"

Mesh::Mesh(const float vertices[], const unsigned int verticesLength, const float texCoords[], const unsigned int texCoordsLength, const unsigned int indices[], const unsigned int indicesLength) {
	// Vertex VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex VBO
	glGenBuffers(1, &vertVbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesLength, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// Texture Coordinates VBO
	glGenBuffers(1, &texVbo);
	glBindBuffer(GL_ARRAY_BUFFER, texVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texCoordsLength, texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);

	// Element buffer object
	glGenBuffers(1, &indEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesLength, indices, GL_STATIC_DRAW);

	// Unbinding
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::bind() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indEbo);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &indEbo);
	glDeleteBuffers(1, &vertVbo);
	glDeleteVertexArrays(1, &vao);
}