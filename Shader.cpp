#include <fstream>
#include <iostream>
#include <string>

#include "Shader.h"

//ctors
Shader::Shader(std::string vertexShaderFile, std::string fragmentShaderFile) {
	GLuint vertexShader, fragmentShader;

	//Create shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	//Read source for vertex shader
	std::string vertexShaderSourceBuffer = readShaderSource(vertexShaderFile);
	const char* vertexShaderSource = vertexShaderSourceBuffer.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	
	//Read source for fragment shader
	std::string fragmentShaderSourceBuffer = readShaderSource(fragmentShaderFile);
	const char* fragmentShaderSource = fragmentShaderSourceBuffer.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	
	//Compile Shaders
	glCompileShader(vertexShader);
	verifyShader(vertexShader, "Vertex");
	glCompileShader(fragmentShader);
	verifyShader(fragmentShader, "Fragment");

	//Link and discard shaders
	createProgram(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return;
}

Shader::Shader() : Shader("vertexShader.vert", "fragmentShader.frag"){
	return;
}

Shader::~Shader(){
}

//Public Member Functions
void Shader::use() {
	glUseProgram(_program);
	return;
}
GLuint Shader::program() {
	return _program;
}
void Shader::modifyUniform(const std::string &uniform, GLint x) {
	GLint uniformLocation = glGetUniformLocation(_program, uniform.c_str());
	verifyUniform(uniformLocation, uniform);
	glUniform1i(uniformLocation, x);
}
void Shader::modifyUniform(const std::string &uniform, GLfloat x) {
	GLint uniformLocation = glGetUniformLocation(_program, uniform.c_str());
	verifyUniform(uniformLocation, uniform);
	glUniform1f(uniformLocation, x);
}
void Shader::modifyUniform(const std::string &uniform, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	GLint uniformLocation = glGetUniformLocation(_program, uniform.c_str());
	verifyUniform(uniformLocation, uniform);
	glUniform4f(uniformLocation, x, y, z, w);
	return;
}

//Private member functions

std::string Shader::readShaderSource(std::string fileName) {
	std::ifstream ifs;
	std::string sourceBuffer;
	std::string lineBuffer;
	
	ifs.open(fileName);
	if (!ifs.is_open()) {
		std::cout << "\n**ERROR** shader" << fileName << "not found.";
		return "";
	}

	while (std::getline(ifs, lineBuffer)) {
		sourceBuffer += lineBuffer + "\n";
	}
	ifs.close();
	
	return sourceBuffer;
}

void Shader::verifyShader(GLuint shader, std::string name) {
	int success;
	char errorLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, errorLog);
		std::cout << "\n**ERROR**: " +  name + " shader compilation failed.\n" << errorLog << std::endl;
	}
	return;
}

void Shader::createProgram(GLuint vertexShader, GLuint fragmentShader) {
	_program = glCreateProgram();
	glAttachShader(_program, vertexShader);
	glAttachShader(_program, fragmentShader);
	glLinkProgram(_program);
	
	return;
}

void Shader::verifyUniform(GLuint uniformLocation, const std::string &uniform) {
	if (uniformLocation == -1) {
		std::cout << "\n**Error** uniform " << uniform << " not found.";
		return;
	}
}