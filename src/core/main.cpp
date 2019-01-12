#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include "core/shader.h"

using namespace std;

static unsigned int constructTriangle() {
	// Location data
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // V0
		-0.5f,  0.5f, 0.0f, // V1
		 0.5f,  0.5f, 0.0f, // V2
		 0.5f, -0.5f, 0.0f  // V3
	};
	unsigned int indices[] = {
		0, 1, 2, // Triangle 1
		2, 3, 0  // Triangle 2
	};

	// Vertex VAO
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex VBO
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Element buffer object
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	return vao;
}

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

	// Load shaders
	string vertFile = string("src/shaders/vert.glsl");
	string fragFile = string("src/shaders/frag.glsl");
	Shader shader(vertFile, fragFile);
	shader.use();

	// Load vertex data
	unsigned int vao = constructTriangle(); // TODO: will use vao ref later

	// Game loop
	bool drawWireframes = false;
	Vec3 amount(0, 0, 0);
	const float INC = 0.01f;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Do updating here
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

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // (Triangle VAO is bound)

		glfwSwapBuffers(window);
	}

	// Clean up resources
	glfwTerminate();

	return 0;
}