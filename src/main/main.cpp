#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "management/init.h"
#include "rendering/shader.h"
#include "ecs/gameObject.h"
#include "controls/camera.h"
#include "terrain/terrain.h"
#include "lights/light.h"
#include "lights/directionalLight.h"
#include "controls/controls.h"
#include "objects/cube.h"
#include "management/window.h"

using namespace std;

constexpr bool PRINT_FPS = true;

int main() {
	cout << "Launching game...\n";

	Window * window = initGLFW(1200, 800, "Dank memes!");

	// Load shaders
	Shader * shader = new Shader("src/shaders/objectVert.glsl", "src/shaders/objectFrag.glsl");
	shader->use();
	Mat4 * projectionMatrix = genPerspectiveProjectionMatrix(45, window->getAspectRatio(), 0.1f, 1000);
	shader->setMat4("projection", *projectionMatrix);
	delete projectionMatrix;

	// Create camera
	Vec3 * pos = new Vec3(0, 0, 0);
	Vec3 * forward = new Vec3(0, 0, 1);
	Vec3 * up = new Vec3(0, 1, 0);
	Camera * cam = new Camera(pos, forward, up);

	// Add lights
	Vec3 * lightColor = new Vec3(1.0f, 1.0f, 1.0f);
	Vec3 * direction = new Vec3(-0.5f, -1.0f, -0.5f);
	DirectionalLight * directionalLight = new DirectionalLight(lightColor, 1.0f, direction);
	directionalLight->load(*shader);

	// Construct objects
	Mesh * mesh = new Mesh(CUBE_VERTICES, sizeof(CUBE_VERTICES), CUBE_TEX_COORDS, sizeof(CUBE_TEX_COORDS), CUBE_NORMALS, sizeof(CUBE_NORMALS), CUBE_INDICES, sizeof(CUBE_INDICES), false);
	Texture * texture = new Texture("res/dirt.png");
	Material * material = new Material(new Vec3(0, 0, 0), 0.2f, 0.5f, 0.2f, 8);
	material->attachDiffuseMap(texture);
	GameObject * object = new GameObject(0, 10.5f, 0, 0, 0, 0, 1, 1, 1, mesh, material, shader);

	Material * terrainMaterial = new Material(new Vec3(0.4f, 0.4f, 0.4f), 0.1f, 0.6f, 0.0f, 32);
	Terrain * terrain = new Terrain(shader, cam, terrainMaterial, 96865);

	// Game loop
	unsigned int frames = 0;
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window->getGLFWwindow())) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//
		// Do updating here
		//

		checkControls(window, cam, shader, terrain);

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
		glfwSwapBuffers(window->getGLFWwindow());
	}

	// Clean up resources
	delete object;
	delete mesh;
	delete material;
	delete terrain;
	delete cam;
	delete directionalLight;
	delete shader;
	delete window;
	glfwTerminate();

	return 0;
}