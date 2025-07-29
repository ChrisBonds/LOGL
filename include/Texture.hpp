#pragma once
#include <glad/glad.h>
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


class Texture {

public:
	Texture(const std::filesystem::path& file_path);
	~Texture();

	void bind(GLenum unit = GL_TEXTURE0)const;//bind to a specified texture slot per draw call
	void unbind()const;
	GLuint getID()const;

private : 
	GLuint ID_;
	void loadFromFile(const std::filesystem::path& file_path); //use in constructor

};