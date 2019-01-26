#include "gameObject.h"

void GameObject::render() {
	Mat4 * mat = genTransformationMatrix(x, y, z, rX, rY, rZ, sX, sY, sZ);
	shader->setMat4("transform", *mat);
	delete mat;

	mesh->bind();
	material->loadAndBind(*shader);

	if (mesh->shouldDrawStrip()) {
		glDrawElements(GL_TRIANGLE_STRIP, mesh->getNumIndices(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawElements(GL_TRIANGLES, mesh->getNumIndices(), GL_UNSIGNED_INT, 0);
	}
	
	unbindTexture(0);
	unbindBuffers();
}