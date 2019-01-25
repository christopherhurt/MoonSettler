#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "init.h"
#include "shader.h"
#include "gameObject.h"
#include "camera.h"
#include "terrain/terrain.h"
#include "lights/light.h"
#include "lights/directionalLight.h"

using namespace std;

constexpr bool PRINT_FPS = true;

static const float vertices[] = {
	-0.5f, -0.5f, -0.5f, // V0
	-0.5f,  0.5f, -0.5f, // V1
	 0.5f,  0.5f, -0.5f, // V2
	 0.5f, -0.5f, -0.5f, // V3
	 0.5f, -0.5f,  0.5f, // V4
	 0.5f,  0.5f,  0.5f, // V5
	-0.5f,  0.5f,  0.5f, // V6
	-0.5f, -0.5f,  0.5f, // V7
	-0.5f, -0.5f,  0.5f, // V8
	-0.5f,  0.5f,  0.5f, // V9
	-0.5f,  0.5f, -0.5f, // V10
	-0.5f, -0.5f, -0.5f, // V11
	 0.5f, -0.5f, -0.5f, // V12
	 0.5f,  0.5f, -0.5f, // V13
	 0.5f,  0.5f,  0.5f, // V14
	 0.5f, -0.5f,  0.5f, // V15
	-0.5f,  0.5f, -0.5f, // V16
	-0.5f,  0.5f,  0.5f, // V17
	 0.5f,  0.5f,  0.5f, // V18
	 0.5f,  0.5f, -0.5f, // V19
	-0.5f, -0.5f,  0.5f, // V20
	-0.5f, -0.5f, -0.5f, // V21
	 0.5f, -0.5f, -0.5f, // V22
	 0.5f, -0.5f,  0.5f  // V23
};

static const float texCoords[] = {
	0.25f, 0.5f,  // V0
	0.25f, 0.75f, // V1
	0.5f,  0.75f, // V2
	0.5f,  0.5f,  // V3
	0.5f,  0.25f, // V4
	0.5f,  0.0f,  // V5
	0.25f, 0.0f,  // V6
	0.25f, 0.25f, // V7
	0.0f,  0.5f,  // V8
	0.0f,  0.75f, // V9
	0.25f, 0.75f, // V10
	0.25f, 0.5f,  // V11
	0.5f,  0.5f,  // V12
	0.5f,  0.75f, // V13
	0.75f, 0.75f, // V14
	0.75f, 0.5f,  // V15
	0.25f, 0.75f, // V16
	0.25f, 1.0f,  // V17
	0.5f,  1.0f,  // V18
	0.5f,  0.75f, // V19
	0.25f, 0.25f, // V20
	0.25f, 0.5f,  // V21
	0.5f,  0.5f,  // V22
	0.5f,  0.25f  // V23
};

static const float normals[] = {
	 0,  0, -1, // V0
	 0,  0, -1, // V1
	 0,  0, -1, // V2
	 0,  0, -1, // V3
	 0,  0,  1, // V4
	 0,  0,  1, // V5
	 0,  0,  1, // V6
	 0,  0,  1, // V7
	-1,  0,  0, // V8
	-1,  0,  0, // V9
	-1,  0,  0, // V10
	-1,  0,  0, // V11
	 1,  0,  0, // V12
	 1,  0,  0, // V13
	 1,  0,  0, // V14
	 1,  0,  0, // V15
	 0,  1,  0, // V16
	 0,  1,  0, // V17
	 0,  1,  0, // V18
	 0,  1,  0, // V19
	 0, -1,  0, // V20
	 0, -1,  0, // V21
	 0, -1,  0, // V22
	 0, -1,  0  // V23
};

static const unsigned int indices[] = {
	0,  1,  2,  2,  3,  0,  // Front
	4,  5,  6,  6,  7,  4,  // Back
	8,  9,  10, 10, 11, 8,  // Left
	12, 13, 14, 14, 15, 12, // Right
	16, 17, 18, 18, 19, 16, // Top
	20, 21, 22, 22, 23, 20  // Down
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

	// Add lights
	Vec3 * lightColor = new Vec3(1.0f, 1.0f, 1.0f);
	Vec3 * direction = new Vec3(0.0f, -1.0f, 0.0f);
	DirectionalLight * directionalLight = new DirectionalLight(lightColor, 1.0f, direction);
	
	// Construct objects
	Mesh * mesh = new Mesh(vertices, sizeof(vertices), texCoords, sizeof(texCoords), normals, sizeof(normals), indices, sizeof(indices), false);
	Texture * texture = new Texture("res/dirt.png");
	Material * material = new Material(texture, 0.2f, 0.5f, 0.2f, 8);
	GameObject * object = new GameObject(0, 0, 0, 0, 0, 0, 1, 1, 1, mesh, material, shader);

	Texture * terrainTex = new Texture("res/terrain.png");
	Material * terrainMaterial = new Material(terrainTex, 0.1f, 0.6f, 0.0f, 32);
	Terrain * terrain = new Terrain(10, 40, shader, cam, terrainMaterial, 234523);

	// Game loop
	unsigned int frames = 0;
	double lastTime = glfwGetTime();
	bool drawWireframes = false;
	const float MOVE_SPEED = 0.1f;
	const float ROT_SPEED = 3.0f;
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
		bool leftHeld = glfwGetKey(window, GLFW_KEY_LEFT);
		bool rightHeld = glfwGetKey(window, GLFW_KEY_RIGHT);
		bool downHeld = glfwGetKey(window, GLFW_KEY_DOWN);
		bool upHeld = glfwGetKey(window, GLFW_KEY_UP);
		if (leftHeld && !rightHeld) {
			cam->turnHorizontal(ROT_SPEED);
		}
		if (rightHeld && !leftHeld) {
			cam->turnHorizontal(-ROT_SPEED);
		}
		if (downHeld && !upHeld) {
			cam->turnVertical(ROT_SPEED);
		}
		if (upHeld && !downHeld) {
			cam->turnVertical(-ROT_SPEED);
		}

		cam->update(*shader);

		// Lighting
		Vec3 * lightDir = directionalLight->getDirection();
		lightDir->x = (float)cos(glfwGetTime());
		lightDir->z = (float)sin(glfwGetTime());
		directionalLight->load(*shader);

		// Render objects (last)
		terrain->updateAndRender();
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
	delete mesh;
	delete material;
	delete terrain;
	delete cam;
	delete directionalLight;
	delete shader;
	glfwTerminate();

	return 0;
}