#pragma once
#include <glad/glad.h>
#include <filesystem>
#include <iostream>
#include "structs/TextureInfo.hpp"
//texture can be a single instance and textures can manage the array of textures? j

//prolly gonna be a big guy theres lots of cool texturing stuff to do

class Texture {
public:
	//allow a default constructor?
	Texture(const TextureInfo& info);
	~Texture();

	void bind(GLenum unit = GL_TEXTURE0)const;//bind to a specified texture slot per draw call.
	void unbind()const;
	GLuint getID()const;
	TextureInfo getInfo()const;

	//void bindToAShaderAsAUniform(stuff) type function
	//changing of glTexParameteri needs to be just 1 function or maybe makes more sense to manipulate where texture is in main. could just have a getglTexParams for debugging

private : 
	GLuint ID_;
	TextureInfo INFO_;	

	//cant decide whether to return the data to store in the class or not
	void loadFromFile(const std::filesystem::path& file_path); //use in constructor
};