#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include "math/vec3.h"

using namespace std;

class Shader {
public:
	Shader(string &vertFile, string &fragFile);
	void setVec2(string &name, float v0, float v1);
	void setVec3(string &name, Vec3 vec);
	void setVec4(string &name, float v0, float v1, float v2, float v3);
	void setMat4(string &name, float vals[]);
	void setFloat(string &name, float val);
	void setInt(string &name, int val);
	void setBool(string &name, bool val);
	void use();
	~Shader();
private:
	unsigned int program;
};
