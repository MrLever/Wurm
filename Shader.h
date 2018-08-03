#pragma once
#include "glad/glad.h"

class Shader{

	private:
		//Member Variables
		GLuint _program;

		//Member functions
		std::string readShaderSource(std::string fileName);
		void verifyShader(GLuint shader, std::string name);
		void createProgram(GLuint vertexShader, GLuint fragmentShader);
		void modifyUniform(const std::string &uniform, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	public:
		//Constructors
		Shader(std::string vertexShader, std::string fragmentShader);
		Shader();
		~Shader();

		//Member Functions
		void use();
};

