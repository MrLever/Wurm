#include <iostream>
#include <string>

#include "Renderer.h"

Renderer::Renderer(std::string programName, int width, int height) {
	_programName = programName;
	_width = width;
	_height = height;
	renderingContextInit();
	glViewport(0, 0, _width, _height);

	return;
}
Renderer::Renderer() : Renderer("OpenGL RenderingContext", 800, 600){
	return;
}

//Destructor
Renderer::~Renderer(){
	glfwTerminate();
	return;
}

GLFWwindow* Renderer::window() {
	return _window;
}

//Private Functions
void Renderer::renderingContextInit() {
	GLFWinit();
	GLADinit();
	std::cout << "Using OpenGL version: \n\t" << glGetString(GL_VERSION) << "\n";
	return;
}

void Renderer::GLFWinit() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(_width, _height, _programName.c_str(), nullptr, nullptr);

	glfwSetFramebufferSizeCallback(_window, framebufferResizeCallback);
	
	if (_window == nullptr) {
		std::cout << "\n**ERROR** Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(_window);

	return;
}

void Renderer::GLADinit() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "\n**ERROR** Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
	return;
}

void Renderer::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	return;
}