#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	inline Window(GLFWwindow * windowIn, int widthIn, int heightIn, int refreshRateIn) : window(windowIn), width(widthIn), height(heightIn), refreshRate(refreshRateIn) { aspectRatio = (float)widthIn / heightIn; }
	inline GLFWwindow * getGLFWwindow() { return window; }
	inline int getWidth() { return width; }
	inline int getHeight() { return height; }
	inline int getRefreshRate() { return refreshRate; }
	inline float getAspectRatio() { return aspectRatio; }
private:
	GLFWwindow * window;
	int width;
	int height;
	int refreshRate;
	float aspectRatio;
};