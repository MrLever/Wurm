#pragma once
#include "Renderer.h"

class Input
{
public:
	//Constructors
	Input();
	~Input();

	//Public Member Functions
	void processInput(GLFWwindow *window);
};

