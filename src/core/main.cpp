#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>

using namespace std;

static unsigned int constructTriangle() {
	// Location data
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // V0
		-0.5f,  0.5f, 0.0f, // V1
		 0.5f,  0.5f, 0.0f, // V2
		 0.5f, -0.5f, 0.0f  // V3
	};
	unsigned int indices[] = {
		0, 1, 2, // Triangle 1
		2, 3, 0  // Triangle 2
	};

	// Vertex VAO
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex VBO
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Element buffer object
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	return vao;
}

static unsigned int constructShaders() {
	// Vertex shader
	ifstream vertFile("src/shaders/vert.glsl");
	string vertSourceStr((istreambuf_iterator<char>(vertFile)), istreambuf_iterator<char>());
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
	ifstream fragFile("src/shaders/frag.glsl");
	string fragSourceStr((istreambuf_iterator<char>(fragFile)), istreambuf_iterator<char>());
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
	glUseProgram(shaderProg);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	return shaderProg;
}

int main() {
	cout << "Launching game...\n";
	
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create window
	const int width = 800;
	const int height = 800;
	const char * title = "Dank memes!";
	GLFWwindow * window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow * window, int width, int height) { glViewport(0, 0, width, height); });

	// Check GLAD loading
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "Failed to initialize GLAD\n";
		return -1;
	}

	// Set background color
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	// Load shaders
	unsigned int shader = constructShaders(); // TODO: will use shader ref later

	// Load vertex data
	unsigned int vao = constructTriangle(); // TODO: will use vao ref later

	// Game loop
	bool drawWireframes = false;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Do updating here
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_M)) {
			if (drawWireframes) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			drawWireframes = !drawWireframes;
		}

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // (Triangle VAO is bound)

		glfwSwapBuffers(window);
	}

	// Clean up resources
	glfwTerminate();

	return 0;
}