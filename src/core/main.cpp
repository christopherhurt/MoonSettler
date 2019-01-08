#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int main() {
	cout << "Launching game...\n";
	
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create window
	const int width = 800;
	const int height = 800;
	const char * title = "Dank memes!";
	GLFWwindow * window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow * window, int width, int height) { glViewport(0, 0, width, height); });

	// Check GLAD loading
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "Failed to initialize GLAD\n";
		return -1;
	}

	// Set background color
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	// Game loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// TODO: do updating here
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	// Clean up resources
	glfwTerminate();

	return 0;
}