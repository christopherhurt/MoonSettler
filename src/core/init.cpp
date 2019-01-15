#include "init.h"

GLFWwindow * initGLFW(const unsigned int width, const unsigned int height, const char * title) {
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create window
	GLFWwindow * window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		exit(-1);
	}
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow * window, int width, int height) { glViewport(0, 0, width, height); });
	glfwMakeContextCurrent(window);

	// Check GLAD loading
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "Failed to initialize GLAD\n";
		exit(-1);
	}

	// Set configurations
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	stbi_set_flip_vertically_on_load(true);

	return window;
}