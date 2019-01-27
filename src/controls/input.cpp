#include "input.h"

static std::vector<bool> keysPressed(NUM_KEYS, false);
static std::vector<bool> keysDown(NUM_KEYS, false);
static std::vector<bool> keysReleased(NUM_KEYS, false);
static std::vector<bool> buttonsPressed(NUM_BUTTONS, false);
static std::vector<bool> buttonsDown(NUM_BUTTONS, false);
static std::vector<bool> buttonsReleased(NUM_BUTTONS, false);

void updateInput(Window * window) {
	for (int key = 0; key < NUM_KEYS; key++) {
		bool keyDown = glfwGetKey(window->getGLFWwindow(), key);
		keysReleased[key] = keysDown[key] && !keyDown;
		keysPressed[key] = !keysDown[key] && keyDown;
		keysDown[key] = keyDown;
	}

	for (int button = 0; button < NUM_BUTTONS; button++) {
		bool buttonDown = glfwGetMouseButton(window->getGLFWwindow(), button);
		buttonsReleased[button] = buttonsDown[button] && !buttonDown;
		buttonsPressed[button] = !buttonsDown[button] && buttonDown;
		buttonsDown[button] = buttonDown;
	}
}

bool keyPressed(int key) {
	return keysPressed[key];
}

bool keyDown(int key) {
	return keysDown[key];
}

bool keyReleased(int key) {
	return keysReleased[key];
}

bool buttonPressed(int button) {
	return buttonsPressed[button];
}

bool buttonDown(int button) {
	return buttonsDown[button];
}

bool buttonReleased(int button) {
	return buttonsReleased[button];
}