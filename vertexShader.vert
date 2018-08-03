#version 450 core

//This is where the conversion between screen coordinates
//and normalized device coordinates usually happens.

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	color = aColor;
}
