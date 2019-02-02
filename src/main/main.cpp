#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "management/init.h"
#include "rendering/shader.h"
#include "ecs/gameObject.h"
#include "controls/camera.h"
#include "terrain/terrain.h"
#include "terrain/terrainGen.h"
#include "lights/light.h"
#include "lights/directionalLight.h"
#include "controls/controls.h"
#include "objects/cube.h"
#include "management/window.h"
#include "skybox/skybox.h"

using namespace std;

constexpr bool PRINT_FPS = true;
constexpr unsigned int SEED = 2930238;

int main() {
	cout << "Launching game...\n";

	Window * window = initGLFW(1200, 800, "Dank memes!");

	// Load shaders
	Shader * shader = new Shader("src/shaders/objectVert.glsl", "src/shaders/objectFrag.glsl");
	Shader * skyboxShader = new Shader("src/shaders/skyboxVert.glsl", "src/shaders/skyboxFrag.glsl");
	Mat4 * projectionMatrix = genPerspectiveProjectionMatrix(45, window->getAspectRatio(), 0.1f, 1000);
	shader->use();
	shader->setMat4("projection", *projectionMatrix);
	skyboxShader->use();
	skyboxShader->setMat4("projection", *projectionMatrix);
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
	shader->use();
	directionalLight->load(*shader);

	// Create skybox
	const char * skyboxTextures[] = { "res/skyboxTemp/R.png", "res/skyboxTemp/L.png", "res/skyboxTemp/U.png", "res/skyboxTemp/D.png", "res/skyboxTemp/F.png", "res/skyboxTemp/B.png" };
	Skybox * skybox = new Skybox(skyboxTextures, skyboxShader);

	// Construct objects
	Mesh * mesh = new Mesh(CUBE_VERTICES, sizeof(CUBE_VERTICES), CUBE_TEX_COORDS, sizeof(CUBE_TEX_COORDS), CUBE_NORMALS, sizeof(CUBE_NORMALS), CUBE_INDICES, sizeof(CUBE_INDICES), false);
	Texture * texture = new Texture("res/dirt.png");
	Material * material = new Material(new Vec3(0, 0, 0), 0.2f, 0.5f, 0.2f, 8);
	material->attachDiffuseMap(texture);
	GameObject * object = new GameObject(0, getCompositeHeightAt(0, 0, SEED) + 1, 0, 0, 0, 0, 1, 1, 1, mesh, material, shader);

	Material * terrainMaterial = new Material(new Vec3(0.25f, 0.25f, 0.25f), 0.1f, 0.6f, 0.0f, 32);
	Terrain * terrain = new Terrain(shader, cam, terrainMaterial, SEED);

	// Game loop
	unsigned int frames = 0;
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window->getGLFWwindow())) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//
		// Do updating here
		//

		// Camera and controls
		checkControls(window, cam, terrain);
		Mat4 * viewMatrix = cam->constructViewMatrix();

		// Render objects (second-to-last)
		shader->use();
		shader->setMat4("view", *viewMatrix);
		shader->setVec3("camLoc", *cam->getPos());

		terrain->updateAndRender();
		object->render();

		// Render skybox (last)
		skyboxShader->use();
		skyboxShader->setMat4("view", *viewMatrix);

		Vec3 rot(0, (float)glfwGetTime() * -5, 0);
		skybox->setRotation(rot);

		skybox->render();

		delete viewMatrix;

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
	delete skybox;
	delete shader;
	delete skyboxShader;
	delete window;
	glfwTerminate();

	return 0;
}