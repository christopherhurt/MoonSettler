#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <stb_image.h>

using namespace std;

class Texture {
public:
	Texture(string &texFile);
	void bindToUnit(unsigned int unit);
	inline unsigned int getId() { return tex; }
	~Texture();
private:
	unsigned int tex;
};