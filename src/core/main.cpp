#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include "shader.h"
#include "gameObject.h"

using namespace std;

static const float vertices[] = {
	-0.5f, -0.5f, 0.0f, // V0
	-0.5f,  0.5f, 0.0f, // V1
	 0.5f,  0.5f, 0.0f, // V2
	 0.5f, -0.5f, 0.0f  // V3
};

static const float texCoords[] = {
	0.0f, 0.0f, // V0
	0.0f, 1.0f, // V1
	1.0f, 1.0f, // V2
	1.0f, 0.0f  // V3
};

static const unsigned int indices[] = {
	0, 1, 2, // Triangle 1
	2, 3, 0  // Triangle 2
};

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

	// Set configurations
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	stbi_set_flip_vertically_on_load(true);
	
	// Load shaders
	string vertFile = string("src/shaders/vert.glsl");
	string fragFile = string("src/shaders/frag.glsl");
	Shader shader(vertFile, fragFile);
	shader.use();

	// Construct objects
	Mesh * mesh = new Mesh(vertices, 12, texCoords, 8, indices, 6);
	string texFile("res/rip.png");
	Texture * texture = new Texture(texFile);
	GameObject * object = new GameObject(mesh, texture);

	// Game loop
	bool drawWireframes = false;
	Vec3 amount(0, 0, 0);
	const float INC = 0.01f;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//
		// Do updating here
		//

		glfwPollEvents();

		// Toggle draw mode
		if (glfwGetKey(window, GLFW_KEY_M)) {
			if (drawWireframes) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			drawWireframes = !drawWireframes;
		}

		// Color changing
		bool colorUpdated = false;
		if (glfwGetKey(window, GLFW_KEY_I)) {
			amount.x += INC;
			colorUpdated = true;
		}
		if (glfwGetKey(window, GLFW_KEY_O)) {
			amount.y += INC;
			colorUpdated = true;
		}
		if (glfwGetKey(window, GLFW_KEY_P)) {
			amount.z += INC;
			colorUpdated = true;
		}

		if (colorUpdated) {
			string amountName("amount");
			shader.setVec3(amountName, amount);
		}

		object->render();

		glfwSwapBuffers(window);
	}

	// Clean up resources
	delete object;
	glfwTerminate();

	return 0;
}