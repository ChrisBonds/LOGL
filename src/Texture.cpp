//have to put this in implementation to avoid linker conflict
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.hpp"

//must be able to distinguish between RGB and RGBA

Texture::Texture(const TextureInfo& info) {
	
	INFO_ = info;
	INFO_.printTextureInfo();


	//change all these 
	glGenTextures(1, &ID_);
	//hardcode this shit cuz im tired
	glBindTexture(INFO_.textureDimension, ID_);
	glTexParameteri(INFO_.textureDimension, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(INFO_.textureDimension, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(INFO_.textureDimension, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(INFO_.textureDimension, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void Texture::bind() {
	glBindTexture(INFO_.textureDimension, ID_);

	glTexParameteri(INFO_.textureDimension, GL_TEXTURE_WRAP_S, INFO_.wrapMode);
	glTexParameteri(INFO_.textureDimension, GL_TEXTURE_WRAP_T, INFO_.wrapMode);
	glTexParameteri(INFO_.textureDimension, GL_TEXTURE_MIN_FILTER, INFO_.minFilter);
	glTexParameteri(INFO_.textureDimension, GL_TEXTURE_MAG_FILTER, INFO_.magFilter);

	//stbi_set_flip_vertically_on_load(INFO_.flipVertically); //this should be called on load instead
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
		glTexImage2D(INFO_.textureDimension, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //pretty sure this is supposed to be a reference
		glGenerateMipmap(INFO_.textureDimension);
	}
	else {
		std::cout << "failed to load texture data from : " << file_path << std::endl;
	}
	stbi_image_free(data); //pretty sure this is supposed to be a reference
}

Texture::~Texture() {
	glDeleteTextures(1, &ID_);
}