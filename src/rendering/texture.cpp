#include "texture.h"

Texture::Texture(const char * texFile) {
	// Loading image data
	int width;
	int height;
	int numChannels;
	unsigned char * data = stbi_load(texFile, &width, &height, &numChannels, 0);

	// Checking image loading
	if (!data) {
		cerr << "Failed to load texture \"" << texFile << "\"\n";
		system("pause");
		exit(-1);
	}

	// Generating texture, setting parameters, and creating mipmap
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); // TODO
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // TODO
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbinding texture and freeing stb resources
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void Texture::bindToUnit(unsigned int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, tex);
}

Texture::~Texture() {
	glDeleteTextures(1, &tex);
}