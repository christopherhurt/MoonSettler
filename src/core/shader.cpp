#include "shader.h"

Shader::Shader(const char * vertFile, const char * fragFile) {
	// Vertex shader
	ifstream vertStream(vertFile);
	string vertSourceStr((istreambuf_iterator<char>(vertStream)), istreambuf_iterator<char>());
	const char * vertSource = vertSourceStr.c_str();
	unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSource, NULL);
	glCompileShader(vertShader);

	// Check vertex shader
	int success;
	const int LOG_LEN = 1024;
	char log[LOG_LEN];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertShader, LOG_LEN, NULL, log);
		cerr << "Error in vertex shader:\n" << log << endl;
		exit(-1);
	}

	// Fragment shader
	ifstream fragStream(fragFile);
	string fragSourceStr((istreambuf_iterator<char>(fragStream)), istreambuf_iterator<char>());
	const char * fragSource = fragSourceStr.c_str();
	unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, NULL);
	glCompileShader(fragShader);

	// Check fragment shader
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragShader, LOG_LEN, NULL, log);
		cerr << "Error in fragment shader:\n" << log << endl;
		exit(-1);
	}

	// Shader program
	unsigned int shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertShader);
	glAttachShader(shaderProg, fragShader);
	glLinkProgram(shaderProg);

	// Check shader program
	glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProg, LOG_LEN, NULL, log);
		cerr << "Shader linking failed:\n" << log << endl;
		exit(-1);
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	
	program = shaderProg;
}

void Shader::setVec2(const char * name, float v0, float v1) {
	glUniform2f(glGetUniformLocation(program, name), v0, v1);
}

void Shader::setVec3(const char * name, Vec3 &vec) {
	glUniform3f(glGetUniformLocation(program, name), vec.x, vec.y, vec.z);
}

void Shader::setVec4(const char * name, float v0, float v1, float v2, float v3) {
	glUniform4f(glGetUniformLocation(program, name), v0, v1, v2, v3);
}

void Shader::setMat4(const char * name, Mat4 &mat) {
	glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_TRUE, mat.getVals());
}

void Shader::setFloat(const char * name, float val) {
	glUniform1f(glGetUniformLocation(program, name), val);
}

void Shader::setInt(const char * name, int val) {
	glUniform1i(glGetUniformLocation(program, name), val);
}

void Shader::setBool(const char * name, bool val) {
	glUniform1i(glGetUniformLocation(program, name), val);
}

void Shader::use() {
	glUseProgram(program);
}

Shader::~Shader() {
	glDeleteProgram(program);
}