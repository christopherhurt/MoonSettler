#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "init.h"
#include "shader.h"
#include "gameObject.h"
#include "camera.h"

using namespace std;

constexpr bool PRINT_FPS = true;

static const float vertices[] = {
	-0.5f, -0.5f, -0.5f, // V0
	-0.5f,  0.5f, -0.5f, // V1
	 0.5f,  0.5f, -0.5f, // V2
	 0.5f, -0.5f, -0.5f, // V3
	-0.5f,  0.5f,  0.5f, // V4
	 0.5f,  0.5f,  0.5f, // V5
	-0.5f, -0.5f,  0.5f, // V6
	-0.5f,  0.5f,  0.5f, // V7
	 0.5f, -0.5f,  0.5f, // V8
	 0.5f,  0.5f,  0.5f, // V9
	-0.5f, -0.5f,  0.5f, // V10
	 0.5f, -0.5f,  0.5f, // V11
	-0.5f,  0.5f,  0.5f, // V12
	 0.5f,  0.5f,  0.5f  // V13
};

static const float texCoords[] = {
	0.25f, 0.5f,  // V0
	0.25f, 0.75f, // V1
	0.5f,  0.75f, // V2
	0.5f,  0.5f,  // V3
	0.25f, 1.0f,  // V4
	0.5f,  1.0f,  // V5
	0.0f,  0.5f,  // V6
	0.0f,  0.75f, // V7
	0.75f, 0.5f,  // V8
	0.75f, 0.75f, // V9
	0.25f, 0.25f, // V10
	0.5f,  0.25f, // V11
	0.25f, 0.0f,  // V12
	0.5f,  0.0f   // V13
};

static const unsigned int indices[] = {
	0,  1,  2,  2,  3,  0,  // Front
	11, 13, 12, 12, 10, 11, // Back
	6,  7,  1,  1,  0,  6,  // Left
	3,  2,  9,  9,  8,  3,  // Right
	1,  4,  5,  5,  2,  1,  // Top
	10, 0,  3,  3,  11, 10  // Down
};

int main() {
	cout << "Launching game...\n";

	const unsigned int width = 1200;
	const unsigned int height = 800;
	GLFWwindow * window = initGLFW(width, height, "Dank memes!");

	// Load shaders
	Shader * shader = new Shader("src/shaders/vert.glsl", "src/shaders/frag.glsl");
	shader->use();
	Mat4 * projectionMatrix = genPerspectiveProjectionMatrix(45, width, height, 0.1f, 1000);
	shader->setMat4("projection", *projectionMatrix);
	delete projectionMatrix;

	// Create camera
	Vec3 * pos = new Vec3(0, 0, 0);
	Vec3 * forward = new Vec3(0, 0, 1);
	Vec3 * up = new Vec3(0, 1, 0);
	Camera * cam = new Camera(pos, forward, up);

	// Construct objects
	Mesh * mesh = new Mesh(vertices, sizeof(vertices), texCoords, sizeof(texCoords), indices, sizeof(indices));
	Texture * texture = new Texture("res/dirt.png");
	GameObject * object = new GameObject(0, 0, 5, -45, 45, 0, 1, 1, 1, mesh, texture, shader);

	// Game loop
	unsigned int frames = 0;
	double lastTime = glfwGetTime();
	bool drawWireframes = false;
	const float MOVE_SPEED = 0.08f;
	const float ROT_SPEED = 1.75f;
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

		// Movement
		if (glfwGetKey(window, GLFW_KEY_S)) {
			cam->moveDepth(-MOVE_SPEED);
		}
		if (glfwGetKey(window, GLFW_KEY_W)) {
			cam->moveDepth(MOVE_SPEED);
		}
		if (glfwGetKey(window, GLFW_KEY_A)) {
			cam->moveSide(-MOVE_SPEED);
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			cam->moveSide(MOVE_SPEED);
		}
		if (glfwGetKey(window, GLFW_KEY_F)) {
			cam->moveHeight(-MOVE_SPEED);
		}
		if (glfwGetKey(window, GLFW_KEY_R)) {
			cam->moveHeight(MOVE_SPEED);
		}
		
		// Rotation
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			cam->turnHorizontal(ROT_SPEED);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			cam->turnHorizontal(-ROT_SPEED);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			cam->turnVertical(ROT_SPEED);
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			cam->turnVertical(-ROT_SPEED);
		}

		cam->updateViewMatrix(*shader);

		object->render();

		//
		// End updating
		//

		// Print FPS
		if (PRINT_FPS) {
			frames++;
			double thisTime = glfwGetTime();
			if (thisTime - lastTime >= 1.0) {
				lastTime += 1.0;
				cout << "FPS: " << frames << "\n";
				frames = 0;
			}
		}
		
		// Updating screen
		glfwSwapBuffers(window);
	}

	// Clean up resources
	delete object;
	delete cam;
	delete shader;
	glfwTerminate();

	return 0;
}