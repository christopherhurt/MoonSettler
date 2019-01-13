#include "gameObject.h"

void GameObject::render() {
	Mat4 * mat = genTransformationMatrix(x, y, z, rX, rY, rZ, sX, sY, sZ);
	shader->setMat4("transform", *mat);
	delete mat;

	mesh->bind();
	texture->bindToUnit(0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	unbindTexture(0);
	unbindBuffers();
}

GameObject::~GameObject() {
	delete mesh;
	delete texture;
}