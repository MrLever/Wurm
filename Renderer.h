#pragma once
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer{
	private:
		//Member Variables
		GLFWwindow* _window;
		std::string _programName;
		int _width;
		int _height;

		//Functions
		void renderingContextInit();
		void GLFWinit();
		void GLADinit();
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	public:
		//Constructors
		Renderer(std::string programName, int width, int height);
		Renderer();
		
		//Destructors
		~Renderer();

		//Functions
		GLFWwindow* window();
};

