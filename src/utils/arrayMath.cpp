#include "arrayMath.h"

float * sumFloatArrays(float * arr1, float * arr2, unsigned int arrLength) {
	float * sum = new float[arrLength];

	for (unsigned int i = 0; i < arrLength; i++) {
		sum[i] = arr1[i] + arr2[i];
	}

	return sum;
}