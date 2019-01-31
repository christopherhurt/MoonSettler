#include "init.h"

Window * initGLFW(const unsigned int width, const unsigned int height, const char * title) {
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create window
	GLFWwindow * glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (glfwWindow == NULL) {
		cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		system("pause");
		exit(-1);
	}
	glfwSetFramebufferSizeCallback(glfwWindow, [](GLFWwindow * window, int width, int height) { glViewport(0, 0, width, height); });
	glfwMakeContextCurrent(glfwWindow);

	// Check GLAD loading
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "Failed to initialize GLAD\n";
		system("pause");
		exit(-1);
	}

	// Set configurations
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	stbi_set_flip_vertically_on_load(true);

	GLFWmonitor * monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode * videoMode = glfwGetVideoMode(monitor);
	int refreshRate = videoMode->refreshRate;

	Window * window = new Window(glfwWindow, width, height, refreshRate);
	return window;
}