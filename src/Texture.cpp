//have to put this in implementation to avoid linker conflict
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.hpp"

Texture::Texture(const std::filesystem::path& file_path) {
	
	glGenTextures(1, &ID_);
	//hardcode this shit cuz im tired
	glBindTexture(GL_TEXTURE_2D, ID_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//should seperate into setup and implementation cuz when u do the stuff theres really just a lot of stuff to do and i wanna avoid the annoying boilerplate 
	loadFromFile(file_path);
}

void Texture::loadFromFile(const std::filesystem::path& file_path) {
	int w, h, nChannels;
	unsigned char* data;
	stbi_set_flip_vertically_on_load(true); //not sure if this is a global invocation thing
	//give these guys their own memory for now because ik something is gonna fuck up
	std::string pathString = file_path.string();
	const char* pathCString = pathString.c_str();
	data = stbi_load(pathCString,&w, &h, &nChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //pretty sure this is supposed to be a reference
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load texture data from : " << file_path << std::endl;
	}
	stbi_image_free(data); //pretty sure this is supposed to be a reference
}

Texture::~Texture() {
	glDeleteTextures(1, &ID_);
}