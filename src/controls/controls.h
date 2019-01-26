#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "input.h"
#include "controls/camera.h"
#include "rendering/shader.h"
#include "time.h"
#include "math/trig.h"

constexpr float MOVE_SPEED = 15;
constexpr float ROT_SPEED = 90;

void checkControls(GLFWwindow * window, Camera * cam, Shader * shader);