#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 atexCoord;

out vec2 texCoord;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main(){
	gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	texCoord = atexCoord;
}