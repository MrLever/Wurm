#version 450 core
out vec4 FragColor;
  
in vec3 vertColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    //FragColor = texture(texture1, texCoord) * vec4(fragColor, 1.0);
	FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.5);
}