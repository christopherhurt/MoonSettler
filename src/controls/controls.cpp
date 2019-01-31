#include "controls.h"

static constexpr float GRAVITY = 15;
static constexpr float JUMP_SPEED = 15;

static bool drawWireframes = false;
static bool screenLocked = false;
static float yVelocity = 0;
static bool jumping = false;

void checkControls(Window * window, Camera * cam, Terrain * terrain) {
	glfwPollEvents();
	updateInput(window);
	float delta = calcDeltaTime();

	// Toggle draw mode
	if (keyPressed(GLFW_KEY_M)) {
		if (drawWireframes) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		drawWireframes = !drawWireframes;
	}

	// Jumping and terrain collision
	if (keyPressed(GLFW_KEY_SPACE) && !jumping) {
		yVelocity += JUMP_SPEED;
		jumping = true;
	}

	float newYVelocity = yVelocity - GRAVITY * delta;
	float newYPos = cam->getPos()->y + newYVelocity * delta - 0.5f * GRAVITY * delta * delta;
	yVelocity = newYVelocity;
	cam->getPos()->y = newYPos;

	float camHeight = terrain->getPlayerHeightAt(cam->getPos()->x, cam->getPos()->z);
	if (cam->getPos()->y < camHeight) {
		cam->setHeight(camHeight);
		yVelocity = 0;
		jumping = false;
	}

	// Movement
	bool moveBack = keyDown(GLFW_KEY_S);
	bool moveForward = keyDown(GLFW_KEY_W);
	bool moveLeft = keyDown(GLFW_KEY_A);
	bool moveRight = keyDown(GLFW_KEY_D);
	
	float depthSpeed = 0;
	float sideSpeed = 0;

	if (moveBack) {
		depthSpeed--;
	}
	if (moveForward) {
		depthSpeed++;
	}
	if (moveLeft) {
		sideSpeed--;
	}
	if (moveRight) {
		sideSpeed++;
	}

	if (depthSpeed != 0 && sideSpeed != 0) {
		depthSpeed = depthSpeed > 0 ? COS_45 : -COS_45;
		sideSpeed = sideSpeed > 0 ? COS_45 : -COS_45;
	}

	if (depthSpeed != 0 || sideSpeed != 0) {
		cam->moveDepth(depthSpeed * MOVE_SPEED * delta);
		cam->moveSide(sideSpeed * MOVE_SPEED * delta);
	}

	// Rotation
	if (!screenLocked && buttonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		glfwSetInputMode(window->getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwSetCursorPos(window->getGLFWwindow(), (int)(window->getWidth() / 2), (int)(window->getHeight() / 2));
		screenLocked = true;
	}
	else if (keyPressed(GLFW_KEY_ESCAPE)) {
		glfwSetInputMode(window->getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		screenLocked = false;
	}

	if (screenLocked) {
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window->getGLFWwindow(), &mouseX, &mouseY);

		mouseX = mouseX / window->getWidth() * 2 - 1;
		mouseY = -mouseY / window->getHeight() * 2 + 1;

		float rotXAmt = (float)mouseX;
		float rotYAmt = (float)mouseY;

		cam->turnHorizontal(-rotXAmt * ROT_SPEED / window->getRefreshRate());
		cam->turnVertical(-rotYAmt * ROT_SPEED / window->getRefreshRate());

		glfwSetCursorPos(window->getGLFWwindow(), (int)(window->getWidth() / 2), (int)(window->getHeight() / 2));
	}
}