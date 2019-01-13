#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "init.h"
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

	GLFWwindow * window = initGLFW(800, 800, "Dank memes!");

	// Load shaders
	Shader * shader = new Shader("src/shaders/vert.glsl", "src/shaders/frag.glsl");
	shader->use();

	// Construct objects
	Mesh * mesh = new Mesh(vertices, 12, texCoords, 8, indices, 6);
	Texture * texture = new Texture("res/rip.png");
	GameObject * object = new GameObject(0, 0, 0, 0, 0, 0, 1, 1, 1, mesh, texture, shader);

	// Game loop
	bool drawWireframes = false;
	Vec3 amount(0, 0, 0);
	const float INC = 0.01f;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();

		//
		// Do updating here
		//

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
			shader->setVec3("amount", amount);
		}

		object->render();

		//
		// End updating
		//

		// Updating screen
		glfwSwapBuffers(window);
	}

	// Clean up resources
	delete object;
	delete shader;
	glfwTerminate();

	return 0;
}