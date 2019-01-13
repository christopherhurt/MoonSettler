#include "model.h"

void Model::bind() {
	mesh->bind();
	texture->bindToUnit(0);
}

Model::~Model() {
	delete mesh;
	delete texture;
}