#include "controls.h"

static bool drawWireframes = false;

void checkControls(GLFWwindow * window, Camera * cam, Shader * shader) {
	glfwPollEvents();
	updateInput(window);

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

	// Movement
	bool moveBack = keyDown(GLFW_KEY_S);
	bool moveForward = keyDown(GLFW_KEY_W);
	bool moveLeft = keyDown(GLFW_KEY_A);
	bool moveRight = keyDown(GLFW_KEY_D);
	bool moveDown = keyDown(GLFW_KEY_F);
	bool moveUp = keyDown(GLFW_KEY_R);
	if (moveBack && !moveForward) {
		cam->moveDepth(-MOVE_SPEED);
	}
	else if (moveForward && !moveBack) {
		cam->moveDepth(MOVE_SPEED);
	}
	if (moveLeft && !moveRight) {
		cam->moveSide(-MOVE_SPEED);
	}
	else if (moveRight && !moveLeft) {
		cam->moveSide(MOVE_SPEED);
	}
	if (moveDown && !moveUp) {
		cam->moveHeight(-MOVE_SPEED);
	}
	else if (moveUp && !moveDown) {
		cam->moveHeight(MOVE_SPEED);
	}

	// Rotation
	bool leftHeld = keyDown(GLFW_KEY_LEFT);
	bool rightHeld = keyDown(GLFW_KEY_RIGHT);
	bool downHeld = keyDown(GLFW_KEY_DOWN);
	bool upHeld = keyDown(GLFW_KEY_UP);
	if (leftHeld && !rightHeld) {
		cam->turnHorizontal(ROT_SPEED);
	}
	else if (rightHeld && !leftHeld) {
		cam->turnHorizontal(-ROT_SPEED);
	}
	if (downHeld && !upHeld) {
		cam->turnVertical(ROT_SPEED);
	}
	else if (upHeld && !downHeld) {
		cam->turnVertical(-ROT_SPEED);
	}

	cam->update(*shader);
}