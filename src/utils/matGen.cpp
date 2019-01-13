#include "matGen.h"

Mat4 * genTransformationMatrix(float x, float y, float z, float rX, float rY, float rZ, float sX, float sY, float sZ) {
	float * translationVals = new float[16] {	1, 0, 0, x,
												0, 1, 0, y,
												0, 0, 1, z,
												0, 0, 0, 1 };
	Mat4 * translation = new Mat4(translationVals);

	float * rotationZVals = new float[16] {};
	Mat4 * rotationZ = new Mat4(rotationZVals);

	float * rotationYVals = new float[16] {};
	Mat4 * rotationY = new Mat4(rotationYVals);

	float * rotationXVals = new float[16] {};
	Mat4 * rotationX = new Mat4(rotationXVals);

	float * scaleVals = new float[16] {};
	Mat4 * scale = new Mat4(scaleVals);

	Mat4 * temp1 = *translation * *rotationZ;
	Mat4 * temp2 = *temp1 * *rotationY;
	Mat4 * temp3 = *temp2 * *rotationX;
	Mat4 * transformation = *temp3 * *scale;

	delete translation;
	delete rotationZ;
	delete rotationY;
	delete rotationX;
	delete scale;

	delete temp1;
	delete temp2;
	delete temp3;

	return transformation;
}