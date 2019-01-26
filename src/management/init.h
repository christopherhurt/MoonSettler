#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

using namespace std;

GLFWwindow * initGLFW(const unsigned int width, const unsigned int height, const char * title);