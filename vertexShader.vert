#version 450 core

//This is where the conversion between screen coordinates
//and normalized device coordinates usually happens.
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertColor;
out vec2 texCoord;

void main(){
    gl_Position = vec4(aPos, 1.0);
    vertColor = aColor;
    texCoord = aTexCoord;
}
