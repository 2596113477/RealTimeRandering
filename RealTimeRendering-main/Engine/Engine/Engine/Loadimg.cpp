#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include<GL/glew.h>
#include "Loadimg.h"
#include"stb_image.h"
#include<iostream>

Loadimg::Loadimg(const char* Path)
{
	glGenTextures(1, &TexBuffer);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannel;
	unsigned char* data = stbi_load(Path, &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "load image failed!";
	}
	stbi_image_free(data);
}
