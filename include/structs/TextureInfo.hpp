//helper for texture class initialization 
//should probably just wrap back in 

#include <filesystem>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct TextureInfo {
	std::filesystem::path filePath;
	GLenum format;
	GLenum wrapMode;
	bool flipVertically;
	GLuint textureDimension;
	GLenum minFilter;
	GLenum magFilter;
	GLenum unit;

	// Fix: Use const reference or value for default argument
	TextureInfo(const std::filesystem::path& file_path = std::filesystem::path(),
				GLenum format = GL_RGB, //rf name 
				GLint wrap_mode = GL_REPEAT,
				bool flip_vertically = true, //do not want to call this state every time 
				GLenum texture_dimension = GL_TEXTURE_2D,
		GLenum min_filter = GL_TEXTURE_MIN_FILTER,
		GLenum mag_filter = GL_TEXTURE_MAG_FILTER,
		GLenum texture_unit = GL_TEXTURE0)

				: filePath(file_path), format(format), wrapMode(wrap_mode), flipVertically(flip_vertically), textureDimension(texture_dimension), minFilter(min_filter), magFilter(mag_filter), unit(texture_unit){}

	std::string printTextureInfo() {
		std::cout << "file path : " << filePath << std::endl;
		std::cout << "format : " << format << std::endl;
		std::cout << "wrap mode : " << wrapMode << std::endl;
		std::cout << "flipped vertically : " << flipVertically << std::endl;
		std::cout << "texture dimension: " << textureDimension << std::endl;
		std::cout << "min filter : " << minFilter << std::endl;
		std::cout << "mag filter : " << magFilter << std::endl;
		std::cout << "texture unit : " << unit << "\n\n\n";
	}
};