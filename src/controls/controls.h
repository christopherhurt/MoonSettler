#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "input.h"
#include "controls/camera.h"
#include "rendering/shader.h"

constexpr float MOVE_SPEED = 0.1f;
constexpr float ROT_SPEED = 3.0f;

void checkControls(GLFWwindow * window, Camera * cam, Shader * shader);