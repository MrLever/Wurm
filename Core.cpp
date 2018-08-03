#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Shader.h"
#include "Input.h"

void framebufferResizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(int argc, char *argv[]) {
	Renderer renderingSystem("OpenGL Window", 800, 600);
	Shader shader;
	Input input;
	GLfloat verts[] = {
		-0.5f, -0.5f,  0.0f,  // Bottom Left
		 1.0f,  0.0f,  0.0f,  // Bottom Left color

		 0.0f,  0.5f,  0.0f,  // center
		 0.0f,  1.0f,  0.0f,  // center color

		 0.5f, -0.5f,  0.0f,  // bottom right
		 0.0f,  0.0f,  1.0f   // bottom right color
	};
	GLuint indices[] = {
		0, 1, 2 //1st triangle
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

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	//Main loop
	while (!glfwWindowShouldClose(renderingSystem.window())) {
		float x = 0, y = 0;

		input.processInput(renderingSystem.window(), x, y);

		//Rendering commands
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //State setting fn
		glClear(GL_COLOR_BUFFER_BIT); //State using fn
		
		shader.use();
		shader.modifyUniform("xDeltaPos", x);
		shader.modifyUniform("yDeltaPos", y);
		/*GLfloat r = 0.0f, g = 0.0f, b = 0.0f, z = 1.0f, time;
		time = (GLfloat)glfwGetTime();

		r = (std::sin(time) / 2.0f) + 0.5f;
		g = (std::sin(time + 3.14f) / 2.0f) + 0.5f;
		b = (std::sin(time + 4.71f) / 2.0f) + 0.5f;
		*/
		//shader.modifyUniform("color", r, g, b, z);

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