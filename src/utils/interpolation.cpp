#include "interpolation.h"

float cosineInterpolation(float v1, float v2, float amt) {
	float cosAmt = (float)(1 - cos((double)amt * PI)) / 2;
	return v1 * (1 - cosAmt) + v2 * cosAmt;
}