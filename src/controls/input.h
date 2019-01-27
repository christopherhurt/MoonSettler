#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "management/window.h"

constexpr auto NUM_KEYS = 350;
constexpr auto NUM_BUTTONS = 8;

void updateInput(Window * window);

bool keyPressed(int key);
bool keyDown(int key);
bool keyReleased(int key);
bool buttonPressed(int button);
bool buttonDown(int button);
bool buttonReleased(int button);