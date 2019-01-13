#include "mat4.h"

Mat4 * Mat4::operator*(Mat4 &mat) {
	float * newVals = new float[16];

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			newVals[r * 4 + c] =	(this->vals[r * 4 + 0]) * (mat.vals[0 * 4 + c]) +
									(this->vals[r * 4 + 1]) * (mat.vals[1 * 4 + c]) +
									(this->vals[r * 4 + 2]) * (mat.vals[2 * 4 + c]) +
									(this->vals[r * 4 + 3]) * (mat.vals[3 * 4 + c]);
		}
	}

	return new Mat4(newVals);
}