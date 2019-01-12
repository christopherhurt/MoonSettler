#include "shader.h"

Shader::Shader(string &vertFile, string &fragFile) {
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

void Shader::setVec2(string &name, float v0, float v1) {
	glUniform2f(glGetUniformLocation(program, name.c_str()), v0, v1);
}

void Shader::setVec3(string &name, Vec3 vec) {
	glUniform3f(glGetUniformLocation(program, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::setVec4(string &name, float v0, float v1, float v2, float v3) {
	glUniform4f(glGetUniformLocation(program, name.c_str()), v0, v1, v2, v3);
}

void Shader::setMat4(string &name, float vals[]) {
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, vals);
}

void Shader::setFloat(string &name, float val) {
	glUniform1f(glGetUniformLocation(program, name.c_str()), val);
}

void Shader::setInt(string &name, int val) {
	glUniform1i(glGetUniformLocation(program, name.c_str()), val);
}

void Shader::setBool(string &name, bool val) {
	glUniform1i(glGetUniformLocation(program, name.c_str()), val);
}

void Shader::use() {
	glUseProgram(program);
}

Shader::~Shader() {
	glDeleteProgram(program);
}