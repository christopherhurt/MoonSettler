#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "input.h"
#include "core/camera.h"
#include "core/shader.h"

constexpr float MOVE_SPEED = 0.1f;
constexpr float ROT_SPEED = 3.0f;

void checkControls(GLFWwindow * window, Camera * cam, Shader * shader);