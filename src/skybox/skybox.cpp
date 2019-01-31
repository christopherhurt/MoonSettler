#include "skybox.h"

Skybox::Skybox(const char * textures[]) {
	// Vertex data
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertVbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CUBE_INDICES), CUBE_INDICES, GL_STATIC_DRAW);

	// Texture
	stbi_set_flip_vertically_on_load(false);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

	int width;
	int height;
	int numChannels;
	for (int i = 0; i < 6; i++) {
		unsigned char * data = stbi_load(textures[i], &width, &height, &numChannels, 0);

		if (!data) {
			cerr << "Failed to load skybox texture \"" << textures[i] << "\"\n";
			stbi_image_free(data);
			system("pause");
			exit(-1);
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
}

void Skybox::render() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

	glDepthMask(GL_FALSE);
	glDrawElements(GL_TRIANGLES, sizeof(CUBE_INDICES) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);
}

Skybox::~Skybox() {
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vertVbo);
	glDeleteVertexArrays(1, &vao);

	glDeleteTextures(1, &tex);
}