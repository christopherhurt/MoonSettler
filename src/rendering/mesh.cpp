#include "mesh.h"

Mesh::Mesh(const float vertices[], const unsigned int verticesSize, const float texCoords[], const unsigned int texCoordsSize, const float normals[], const unsigned int normalsSize, const unsigned int indices[], const unsigned int indicesSize, bool drawStripIn) : drawStrip(drawStripIn) {
	numIndices = indicesSize / sizeof(unsigned int);

	// Vertex VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex VBO
	glGenBuffers(1, &vertVbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertVbo);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// Texture Coordinates VBO
	glGenBuffers(1, &texVbo);
	glBindBuffer(GL_ARRAY_BUFFER, texVbo);
	glBufferData(GL_ARRAY_BUFFER, texCoordsSize, texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);

	// Normals VBO
	glGenBuffers(1, &normVbo);
	glBindBuffer(GL_ARRAY_BUFFER, normVbo);
	glBufferData(GL_ARRAY_BUFFER, normalsSize, normals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(2);

	// Element buffer object
	glGenBuffers(1, &indEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

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
	glDeleteBuffers(1, &texVbo);
	glDeleteBuffers(1, &normVbo);
	glDeleteVertexArrays(1, &vao);
}