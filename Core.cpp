#include <iostream>
#include <string>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Shader.h"
#include "Input.h"

/*
	TODO:
	Break this bitch apart.
	Why no color
*/

void framebufferResizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(int argc, char *argv[]) {
	Renderer renderingSystem("OpenGL Window", 800, 600);
	Shader shader;
	Input input;
	GLfloat verts[] = {
		-1.0f,  -1.0f, 0.0f,  // Bottom Left
		 0.0f, -1.0f, 0.0f,  // bottom right
		 0.0f,  0.0f, 0.0f,  // center
		 0.0f,  1.0f, 0.0f,   // center right
		 1.0f, 1.0f, 0.0f
	};
	GLuint indices[] = {
		0, 1, 2, //1st triangle
		2, 3, 4  //2nd triangle
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	
	GLuint VBO;
	glGenBuffers(1, &VBO);
	
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);	


	//Main loop
	while (!glfwWindowShouldClose(renderingSystem.window())) {
		input.processInput(renderingSystem.window());

		//Rendering commands
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //State setting fn
		glClear(GL_COLOR_BUFFER_BIT); //State using fn
		
		shader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		glfwSwapBuffers(renderingSystem.window());
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);


	return 0;
}

void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	return;
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	return;
}