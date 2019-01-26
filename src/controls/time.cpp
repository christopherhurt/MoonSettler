#include "time.h"

static double oldTime = -1;
static float delta = 0;

float calcDeltaTime() {
	if (oldTime < 0) {
		oldTime = glfwGetTime();
		return 0;
	}

	double newTime = glfwGetTime();
	delta = (float)(newTime - oldTime);
	oldTime = newTime;

	return delta;
}

float getDeltaTime() {
	return delta;
}