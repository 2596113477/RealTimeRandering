#version 330 core
out vec4 FragColor;
in vec2 texCoord;


uniform vec3 objColor;

//uniform sampler2D ourTexture;

void main(){
	//vec4 textureColor = texture(ourTexture,texCoord);
	FragColor = vec4(objColor,0);
}