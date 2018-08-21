#include <iostream>
#include <string>

#include "Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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

//Public Functions
GLFWwindow* Renderer::window() {
	return _window;
}

GLuint Renderer::fetchTexture(std::string filepath) {
	//Load image from file
	int width, height, channels;
	unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

	if (data == nullptr) {
		std::cout << "\n**Error** Texture file not found: " << filepath << std::endl;
		return 0;
	}
	
	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Generate texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	
	//Free image data
	stbi_image_free(data);

	return texture;
	//return 0;
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