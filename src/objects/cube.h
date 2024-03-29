#pragma once

const float CUBE_VERTICES[] = {
	-0.5f, -0.5f, -0.5f, // V0
	-0.5f,  0.5f, -0.5f, // V1
	 0.5f,  0.5f, -0.5f, // V2
	 0.5f, -0.5f, -0.5f, // V3
	 0.5f, -0.5f,  0.5f, // V4
	 0.5f,  0.5f,  0.5f, // V5
	-0.5f,  0.5f,  0.5f, // V6
	-0.5f, -0.5f,  0.5f, // V7
	-0.5f, -0.5f,  0.5f, // V8
	-0.5f,  0.5f,  0.5f, // V9
	-0.5f,  0.5f, -0.5f, // V10
	-0.5f, -0.5f, -0.5f, // V11
	 0.5f, -0.5f, -0.5f, // V12
	 0.5f,  0.5f, -0.5f, // V13
	 0.5f,  0.5f,  0.5f, // V14
	 0.5f, -0.5f,  0.5f, // V15
	-0.5f,  0.5f, -0.5f, // V16
	-0.5f,  0.5f,  0.5f, // V17
	 0.5f,  0.5f,  0.5f, // V18
	 0.5f,  0.5f, -0.5f, // V19
	-0.5f, -0.5f,  0.5f, // V20
	-0.5f, -0.5f, -0.5f, // V21
	 0.5f, -0.5f, -0.5f, // V22
	 0.5f, -0.5f,  0.5f  // V23
};

const float CUBE_TEX_COORDS[] = {
	0.25f, 0.5f,  // V0
	0.25f, 0.75f, // V1
	0.5f,  0.75f, // V2
	0.5f,  0.5f,  // V3
	0.5f,  0.25f, // V4
	0.5f,  0.0f,  // V5
	0.25f, 0.0f,  // V6
	0.25f, 0.25f, // V7
	0.0f,  0.5f,  // V8
	0.0f,  0.75f, // V9
	0.25f, 0.75f, // V10
	0.25f, 0.5f,  // V11
	0.5f,  0.5f,  // V12
	0.5f,  0.75f, // V13
	0.75f, 0.75f, // V14
	0.75f, 0.5f,  // V15
	0.25f, 0.75f, // V16
	0.25f, 1.0f,  // V17
	0.5f,  1.0f,  // V18
	0.5f,  0.75f, // V19
	0.25f, 0.25f, // V20
	0.25f, 0.5f,  // V21
	0.5f,  0.5f,  // V22
	0.5f,  0.25f  // V23
};

const float CUBE_NORMALS[] = {
	 0,  0, -1, // V0
	 0,  0, -1, // V1
	 0,  0, -1, // V2
	 0,  0, -1, // V3
	 0,  0,  1, // V4
	 0,  0,  1, // V5
	 0,  0,  1, // V6
	 0,  0,  1, // V7
	-1,  0,  0, // V8
	-1,  0,  0, // V9
	-1,  0,  0, // V10
	-1,  0,  0, // V11
	 1,  0,  0, // V12
	 1,  0,  0, // V13
	 1,  0,  0, // V14
	 1,  0,  0, // V15
	 0,  1,  0, // V16
	 0,  1,  0, // V17
	 0,  1,  0, // V18
	 0,  1,  0, // V19
	 0, -1,  0, // V20
	 0, -1,  0, // V21
	 0, -1,  0, // V22
	 0, -1,  0  // V23
};

const unsigned int CUBE_INDICES[] = {
	0,  1,  2,  2,  3,  0,  // Front
	4,  5,  6,  6,  7,  4,  // Back
	8,  9,  10, 10, 11, 8,  // Left
	12, 13, 14, 14, 15, 12, // Right
	16, 17, 18, 18, 19, 16, // Top
	20, 21, 22, 22, 23, 20  // Down
};