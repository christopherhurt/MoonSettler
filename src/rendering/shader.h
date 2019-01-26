#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include "math/vec3.h"
#include "math/mat4.h"

using namespace std;

class Shader {
public:
	Shader(const char * vertFile, const char * fragFile);
	void setVec2(const char * name, float v0, float v1);
	void setVec3(const char * name, Vec3 &vec);
	void setVec4(const char * name, float v0, float v1, float v2, float v3);
	void setMat4(const char * name, Mat4 &mat);
	void setFloat(const char * name, float val);
	void setInt(const char * name, int val);
	void setBool(const char * name, bool val);
	void use();
	~Shader();
private:
	unsigned int program;
};
