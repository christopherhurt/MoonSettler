#pragma once

class Mat4 {
public:
	inline Mat4(float * valsIn) : vals(valsIn) {}
	Mat4 * operator*(Mat4 &mat);
	inline float * getVals() { return vals; }
	inline ~Mat4() { delete[] vals; }
private:
	float * vals;
};