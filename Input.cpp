#include "Input.h"

//Constructor
Input::Input(){
}

//Destructor
Input::~Input(){
}

void Input::processInput(GLFWwindow *window, float &x, float &y) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		y += 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		y -= 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		x -= 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		x += 0.1f;
	}
	
	return;
}