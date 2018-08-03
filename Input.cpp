#include "Input.h"

//Constructor
Input::Input(){
}

//Destructor
Input::~Input(){
}

void Input::processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	return;
}